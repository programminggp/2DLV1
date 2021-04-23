#include "CPlayer.h"
#include "CKey.h"

#include "CItem.h"
#include "CBullet.h"
#include "CSceneTitle.h"

//衝突時のエフェクト追加
#include "CEffect.h"
extern std::shared_ptr<CTexture> TextureExp;
extern std::shared_ptr<CTexture> TextureHit;
extern std::shared_ptr<CTexture> TextureBoost;
#include "CTaskManager.h"

#include <stdio.h>
#include <math.h>

#define PI 3.141592

extern CSound SoundJump;
extern CSound SoundShot;
extern CSound SoundItemGet;
extern CSound SoundBoost;
extern CSound SoundEngine;
extern CSound SoundHorn;
extern CSound SoundCollision;
extern CSound SoundCollisionSmall;
extern CSound SoundRespawn;
extern CSound SoundRespawn2;

int CPlayer::RenderType;

CPlayer *CPlayer::mpPlayer = 0;

#define G (9.8f / 90.0f)//重力加速度//60.0f
#define JUMPV0 (4.0f*4.0f)//ジャンプ初速//4.0f

#define MAXSPEED 20.0f //4.5f+3.0f *5//車の最高速度
#define MAXSPEED_BACK 1.0f*2 *2//車の後退する最大速度
#define CAR_POWER 0.05f*2 //*2//1フレーム辺りの車の加速していく量
#define CAR_BREAK_POWER 0.025f*2 *2//前進中のブレーキの強さ
//#define MAXSPEED_LIMITUP 10.0f //ブースト中の最高速度の上限突破量

#define DECELERATE 0.05f*2 //車の減速する量
#define FIX_ANGLE_VALUE 0.5f*2 //角度が0度に向けて調整される量(主にX・Z用)

#define JUMPER01_POWER 3.0f;//ジャンプ台1によるジャンプの強さ

//#define MAXSPEED 7.0f //車の最高速度
//#define MAXSPEED_BACK 2.0f //車の後退する最大速度
//#define CAR_POWER 0.1f //1フレーム辺りの車の加速していく量
//#define CAR_BREAK_POWER 0.05f //前進中のブレーキの強さ
//
//#define DECELERATE 0.1f //車の減速する量
//#define FIX_ANGLE_VALUE 0.5f //角度が0度に向けて調整される量(主にX・Z用)

CPlayer::CPlayer()
//車体のY座標は0.0fにしたいんだけど・・・
//0.0fにしたら車体が浮いてるように見えてしまう
:mColBody(this, CVector(0.0f, 4.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f*3)
, mColTire(this, CVector(0.0f, -16.0f + 15.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 3)
//, mColCamRange(this, CVector(0.0f, 20.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 50.0f)
//, mColCamera(this, CVector(0.0f, 17.0f, 40.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 15.0f * 1)
{
	mpPlayer = this;

	mScale = CVector(7.5f, 7.5f, 7.5f);

	mVelocityJump = 0.0f;
	mJumpV0 = 1.1f;//バネ取得後は2.3fの予定
	mMoveSpeed = 0.5f;
	mADMoveX = 0.0f;  mWSMoveZ = 0.0f;
	mCarSpeed = 0.0f;//車の速度の初期化
	mTurnSpeed = 0.0f;
	mBuzzerCount = 0;//ブザーを鳴らした回数
	mRespawnCount = 0;//リスポーンした回数

	mCanJump = false;
	mCanSwim = false;
	mIsGetKey = false;
	mHaveBoat = false;
	mFlyingMode = false;

	CanMove = false;

	mChecks = 0;

	isBoost = false;
	mBoostMaxSpeed = 0.0f;
	mBoostTime = 0;

	mTag = EPLAYER;
	//mColCamRange.mTag = CCollider::ECAMERA_RANGE;
	mJumpPrio = 0;

	if (CSceneTitle::mMode == 3){
		//スタート地点の座標を設定;
		mStartPoint[0] = 0.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = 80.0f;
		mStartRotation = 90.0f;
		mRotation.mY = mStartRotation;
	}
	else if (CSceneTitle::mMode == 2){
		//スタート地点の座標を設定;
		mStartPoint[0] = 2222.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = -2510.0f;
		mStartRotation = 0.0f;
		mRotation.mY = mStartRotation;
	}
	else if (CSceneTitle::mMode == 4){
		//スタート地点の座標を設定;
		mStartPoint[0] = 0.0f;  mStartPoint[1] = 0.0f;  mStartPoint[2] = 0.0f;
		//mStartPoint[0] = 450.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = -50.0f;
		mStartRotation = 180.0f;
		mRotation.mY = mStartRotation;
	}
	else if (CSceneTitle::mMode == 5){
		//スタート地点の座標を設定;
		mStartPoint[0] = -3755.5f;  mStartPoint[1] = 13.5f;  mStartPoint[2] = 16060.5f;
		mStartRotation = -145.0f;
		mRotation.mY = mStartRotation;		
	}	
	else{
		//スタート地点の座標を設定;
		mStartPoint[0] = 350.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = -100.0f;
		mStartRotation = 0.0f;
		mRotation.mY = mStartRotation;
	}
	mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
	CCharacter::Update();

	RenderType = 0;//描画処理 0:ゲーム画面  1:ミニマップ

	mColBody.mTag = CCollider::EBODY;
	mColTire.mTag = CCollider::ESEARCH;
	//mColCamRange.mTag = CCollider::ECAMERA_RANGE;
	//mColCamera.mTag = CCollider::ECAMERA;

	SoundJump.Load("SE\\jump12.wav");
	SoundShot.Load("SE\\shot1.wav");
	SoundItemGet.Load("SE\\se_maoudamashii_system46.wav");	
	SoundBoost.Load("SE\\Shortbridge31-3.wav");
	SoundEngine.Load("SE\\SNES-Racing01-02.wav");
	SoundEngine_Turf.Load("SE\\SNES-Racing02-02.wav");
	SoundHorn.Load("SE\\car-horn1.wav");
	ShutUp.Load("SE\\Hanzawa's_SHOUT_UP!.wav");	
	SoundCollision.Load("SE\\bomb1.wav");
	SoundCollisionSmall.Load("SE\\SNES-Racing01-10(Collision).wav");
	SoundRespawn.Load("SE\\nc31154.wav");
	SoundRespawn2.Load("SE\\nc55733.wav");
	
	
	isSoundEngine = false;
	//SoundEngine.Repeat();
	isTouchGoal = false;
	mGoalTime = 0; mRank = 1;

//	mCamRange = new CCameraRange();
//	mCam = new CCameraPos();
}

void CPlayer::Update(){
	if (CKey::Push('Q')){//でば
		mRotation.mY++;
	}
	if (CKey::Push('E')){//つぐ
		mRotation.mY--;
	}
	if (CKey::Push('Z')){//でば
		mRotation.mX+=10;
	}
	if (CKey::Push('X')){//つぐ
		mRotation.mX-=10;
	}
	if (CKey::Push('C')){//でば
		mRotation.mZ += 10;
	}
	if (CKey::Push('V')){//つぐ
		mRotation.mZ-=10;
	}

	if (CKey::Once(' ')){//クラクションを鳴らす
		SoundHorn.Play();
		mBuzzerCount++;
		if (mBuzzerCount > 0 && mBuzzerCount % 7 == 0){
			ShutUp.Play();
			mBuzzerCount = 0;
		}
	}

	
	//飛行モード有効時(デバッグ用)
	if (mFlyingMode){
		if (CKey::Push('W')){
			mVelocityJump = mMoveSpeed*3;
		}
		else if (CKey::Push('S')){
			mVelocityJump = -mMoveSpeed*3;
		}
		else{
			mVelocityJump = 0.0f;
		}
	}

	//ブースト残り時間
	if (mBoostTime > 0){
		mBoostTime--;
	}
	else{
		isBoost = false;		
	}
	//ブースト有効時
	if (isBoost){
		mBoostMaxSpeed = 10.0f;

		if (mCarSpeed < MAXSPEED + mBoostMaxSpeed){
			//ブースト時のアクセル効果は実質3倍
			mCarSpeed += CAR_POWER;
			mCarSpeed += CAR_POWER;
		}
	}
	//ブーストが切れている時
	else{
		//最高速度が通常まで減速
		if (mBoostMaxSpeed > 0.0f){
			if (mBoostMaxSpeed > 0.2f){
				mBoostMaxSpeed -= 0.2f;
			}
			else{
				mBoostMaxSpeed = 0.0f;
			}
		}
		//ブーストが終了して現在の速度が最高速度を超過していた場合、最高速度に合わせて減速されていく
		if (mCarSpeed > MAXSPEED + mBoostMaxSpeed){
			mCarSpeed = MAXSPEED + mBoostMaxSpeed;
		}
	}


	if (CKey::Push(VK_UP) && CanMove){
		if (mCarSpeed < MAXSPEED + mBoostMaxSpeed){
			mCarSpeed += CAR_POWER;
		}		
	}
	else if (CKey::Push(VK_DOWN) && CanMove){
		if (mCarSpeed > -MAXSPEED_BACK){
			mCarSpeed -= CAR_POWER;
			//前進中ならブレーキがかかり、早めに止まる
			if (mCarSpeed >= CAR_BREAK_POWER){
				mCarSpeed -= CAR_BREAK_POWER;
			}
		}
	}
	else{
		//前進中
		if (mCarSpeed > 0.0f){
			//減速値でマイナスにならないように調整
			if (mCarSpeed < DECELERATE){
				mCarSpeed = 0.0f;
			}
			else{
				mCarSpeed -= DECELERATE;
			}
		}
		//後退中
		else if (mCarSpeed < 0.0f){
			if (mCarSpeed > -DECELERATE){
				mCarSpeed = 0.0f;
			}
			else{
				mCarSpeed += DECELERATE;
			}
		}		
	}

	//////プレイヤーのX角度が0に戻されていく
	////if (mRotation.mX > 0.0f){
	////	if (mRotation.mX > FIX_ANGLE_VALUE){
	////		mRotation.mX -= FIX_ANGLE_VALUE;
	////	}
	////	else{
	////		mRotation.mX = 0.0f;
	////	}
	////}
	////else if (mRotation.mX < 0.0f){
	////	if (mRotation.mX < -FIX_ANGLE_VALUE){
	////		mRotation.mX += FIX_ANGLE_VALUE;
	////	}
	////	else{
	////		mRotation.mX = 0.0f;
	////	}
	////}
	//////プレイヤーのZ角度が0に戻されていく
	////if (mRotation.mZ > 0.0f){
	////	if (mRotation.mZ > FIX_ANGLE_VALUE){
	////		mRotation.mZ -= FIX_ANGLE_VALUE;
	////	}
	////	else{
	////		mRotation.mZ = 0.0f;
	////	}
	////}
	////else if (mRotation.mZ < 0.0f){
	////	if (mRotation.mZ < -FIX_ANGLE_VALUE){
	////		mRotation.mZ += FIX_ANGLE_VALUE;
	////	}
	////	else{
	////		mRotation.mZ = 0.0f;
	////	}
	////}

	if (CKey::Push(VK_LEFT) && CanMove){ //ハンドルを左に！
		//mRotation.mY++;
		if (mTurnSpeed>=0.0f&&mTurnSpeed<0.5f){
			mTurnSpeed = 0.5f;
		}
		if (mTurnSpeed < 0.0f){
			mTurnSpeed += 0.11f;
			//mTurnSpeed += 0.08f;
		}
		mTurnSpeed += 0.04f;
		//mTurnSpeed += 0.02f;
	}
	else if (CKey::Push(VK_RIGHT) && CanMove){//ハンドルを右に！
		//mRotation.mY--;
		if (mTurnSpeed <= 0.0f&&mTurnSpeed>-0.5f){
			mTurnSpeed = -0.5f;
		}
		if (mTurnSpeed > 0.0f){
			mTurnSpeed -= 0.11f;
		}
		mTurnSpeed -= 0.04f;
	}
	else{
		if (mTurnSpeed > 0.0f){
			mTurnSpeed -= 0.05f;
		}
		else if (mTurnSpeed < 0.0f){
			mTurnSpeed += 0.05f;
		}
		if (mTurnSpeed<0.04f && mTurnSpeed>-0.04f){
			mTurnSpeed = 0.0f;
		}
	}
	if (mTurnSpeed > 1.0f){
		mTurnSpeed = 1.0f;
	}
	else if (mTurnSpeed < -1.0f){
		mTurnSpeed = -1.0f;
	}
	mRotation.mY += mTurnSpeed;
	
	if (mRotation.mZ > 180){
		mRotation.mZ = -180;
	}
	else if (mRotation.mZ < -180){
		mRotation.mZ = 180;
	}

	//前に車が進んでいる時
	if (mCarSpeed > 0.0f){
		if (isSoundEngine == false){
			SoundEngine.Repeat();
			isSoundEngine = true;
		}		
	}
	//車が停止している時
	else if (mCarSpeed == 0.0f){
		SoundEngine.Stop();
		isSoundEngine = false;
	}
	//車がバックしている時
	else if (mCarSpeed < 0.0f){
		if (isSoundEngine == false){
			//バックは違う音を鳴らす予定
			SoundEngine.Repeat();
			isSoundEngine = true;
		}
	}

	//mPosition = CVector(mADMoveX, mVelocityJump, mWSMoveZ)  * CMatrix().RotateY(mRotation.mY) * mMatrix;
	//mPosition = CVector(mADMoveX, mVelocityJump, mWSMoveZ) * CMatrix().RotateY(90) * mMatrix;
	//mPosition = CVector(mADMoveX, mVelocityJump, mWSMoveZ+mCarSpeed) * CMatrix().RotateY(90) * mMatrix;
	////常に地面に垂直に落下するようにする(プレイヤーの真下ではない)
	//mPosition = CVector(mADMoveX, mVelocityJump, mWSMoveZ + mCarSpeed) * mMatrix;
	//mPosition = CVector(mADMoveX, 0.0f, mWSMoveZ + mCarSpeed) * mMatrix;
	mPosition = CVector(mADMoveX, 0.0f, mWSMoveZ + mCarSpeed) * mMatrixRotate * mMatrixTranslate;
	CCharacter::Update();
	//Y方向(重力)は分ける
	//mPosition = CVector(0.0f, mVelocityJump, 0.0f) * mMatrix;//できてない
	mPosition = CVector(0.0f, mVelocityJump*2.0f, 0.0f) * //mMatrixScale * 
		CMatrix().RotateZ(0) *
		CMatrix().RotateX(0) *
		CMatrix().RotateY(0)
		*mMatrixTranslate;//できてる？
	//mMatrix = mMatrixScale * mMatrixRotate * mMatrixTranslate;

	//転落してしまった時(Rキーで即リスタート)
	if (mPosition.mY < -700.0f || CKey::Once('R')){
		//落下の勢いを0にする
		mVelocityJump = 0.0f;
		//車の速度を0に
		mCarSpeed = 0.0f;
		////リスタート時の効果音
		//int sr = rand()%2;
		//if (sr == 0){
		//	SoundRespawn.Play();
		//}
		//else{
		//	SoundRespawn2.Play();
		//}
		//mRespawnCount++;
		//int respawntext = 0;
		////5回目までは煽られない
		//if (mRespawnCount <= 5){
		//	respawntext = 0;
		//}
		//else if (mRespawnCount <= 10){
		//	respawntext = rand() % 2;
		//}
		//else{
		//	respawntext = rand() % 3;
		//}
		////リスポーンしすぎると煽られます
		//if (respawntext == 0){
		//	printf("%d-%d\n", 33 * mRespawnCount, 4 * mRespawnCount);
		//}
		//else if (respawntext == 1){
		//	printf("(笑)\n");
		//}
		//else if (respawntext == 2){
		//	if (mRespawnCount < 20){
		//		printf("^^;\n");
		//	}
		//	else if (mRespawnCount < 30){
		//		printf("^^;;;;;\n");
		//	}
		//	else if (mRespawnCount < 50){
		//		printf("^^;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		//	}
		//	else{
		//		printf("^^;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		//	}
		//}

		if (CSceneTitle::mMode == 2){
			if (mChecks == 0){
				//スタート時の位置、方向に戻される
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mStartRotation = 0.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(2893.0f, mStartPoint[1], 2473.0f);
				mStartRotation = -59.0f;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1020.0f, mStartPoint[1], 4594.0f);
				mStartRotation = -506.4f;
			}
			else if (mChecks == 3){
				mPosition = CVector(-1277.0f, mStartPoint[1], -448.0f);
				mStartRotation = -200.0f;
			}
		}
		else if (CSceneTitle::mMode == 3){
			if (mChecks == 0){
				//スタート時の位置、方向に戻される
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mStartRotation = 90.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(1127.4f, mStartPoint[1] + 100.0f, -5054.0f);
				mStartRotation = -59.0f;
			}
			else if (mChecks == 2){
				mPosition = CVector(777.0f, mStartPoint[1], 1925.0f);
				mStartRotation = 405.1f;
			}
			else if (mChecks == 3){
				mPosition = CVector(-5861.0f, mStartPoint[1], 1165.0f);
				mStartRotation = -583.5f;
			}
		}
		else if (CSceneTitle::mMode == 5){
			if (mChecks == 0){
				//スタート時の位置、方向に戻される
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mStartRotation = -145.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(-16054.4f, 4915.0f, -2180.0f);
				mStartRotation = -174.6f;
			}
			else if (mChecks == 2){
				mPosition = CVector(4680.0f, 13.5f, -2027.0f);
				mStartRotation = 147.2f;
			}
			else if (mChecks == 3){
				mPosition = CVector(14809.0f, 13.5f, 4270.0f);
				mStartRotation = -9.5f;
			}
		}
		else{
			if (mChecks == 0){
				//スタート時の位置、方向に戻される
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mStartRotation = 0.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(-80.0f, mStartPoint[1], 2175.0f);
				mStartRotation = -55.0f;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1620.0f, mStartPoint[1], 450.0f);
				mStartRotation = -175.0f;
			}
			else if (mChecks == 3){
				mPosition = CVector(-1212.0f, mStartPoint[1], -1616.0f);
				mStartRotation = 120.0f;
			}
		}
		mRotation = CVector(0.0f, mStartRotation, 0.0f);
		
	}

	CCharacter::Update();
	
	//重力の影響を反映する
	mVelocityJump -= G;
	//if (CKey::Once('K')){
	//	if (mCanJump){
	//		//ボート乗船時はジャンプ不可
	//		if (mHaveBoat){
	//		}
	//		else{
	//			mCanJump = false;
	//			mVelocityJump = mJumpV0;
	//			mJumpPrio = 2;
	//			////ジャンプ音再生
	//			SoundJump.Play();
	//		}
	//	}
	//}
	if (mJumpPrio > 0){
		mJumpPrio--;
	}
	
}

void CPlayer::Collision(CCollider *mc, CCollider *yc){
	//自身のコライダタイプの判定
	switch (mc->mType){
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (yc->mType == CCollider::ETRIANGLE){
			//自分のコライダが本体の時
			if (mc->mTag == CCollider::EBODY){
				//芝生通過中の処理
				if (yc->mpParent->mTag == CCharacter::EGRASS){
					CVector aiueo;//仮のベクトル
					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
						//ブースト効果の方が優先される
						if (isBoost == false){
							//printf("speed down…\n");
							//一定速度までスピード低下
							if (mCarSpeed > 3.2f + 1.8f){
								if (mCarSpeed > 4.0f + 1.8f){
									mCarSpeed -= 0.8f;
								}
								else{
									mCarSpeed = 3.2f +1.8f;
								}
							}
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT){//中間地点1
					if (mChecks == 0){
						//各中間地点を通過しないと1周したとみなされない
						CVector aiu;//数合わせのためだけのベクトル
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							mChecks = 1;
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT2){//中間地点2
					if (mChecks == 1){
						//各中間地点を通過しないと1周したとみなされない
						CVector aiu;//数合わせのためだけのベクトル
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							mChecks = 2;
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT3){//中間地点3
					if (mChecks == 2){
						//各中間地点を通過しないと1周したとみなされない
						CVector aiu;//数合わせのためだけのベクトル
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							mChecks = 3;
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::EGOALPOINT){//中間地点3
					if (mChecks == 3){
						//各中間地点を通過しないと1周したとみなされない
						CVector aiu;//数合わせのためだけのベクトル
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							isTouchGoal = true;
						}
					}
				}
				/*else{
					isTouchGoal = false;
				}*/
				if (mCanSwim && yc->mpParent->mTag == CCharacter::EWATER){
					//通過可能、ステージ1の水
				}
				else if (yc->mpParent->mTag == CCharacter::ECLEARWATER){
					//通過可能、ステージ2の水
				}
				else if (yc->mpParent->mTag == CCharacter::ECHECKPOINT
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT2
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT3
					|| yc->mpParent->mTag == CCharacter::EGOALPOINT
					|| yc->mpParent->mTag == CCharacter::EDASHBOARD){
					//処理は行われるが、これらのパネルは通過可能
				}
				else{
					if (mJumpPrio < 1){

						CVector adjust;//調整用ベクトル
						//		//三角形と球の衝突判定
						//		CCollider::CollisionTriangleSphere(yc, mc, &adjust);
						if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
							//位置の更新
							mPosition = mPosition - adjust * -1;
							//行列の更新
							CCharacter::Update();

							if (yc->mpParent->mTag == CCharacter::EWALL){
								//衝突したのが壁だった場合は壁には引っかからず落下
								//壁にぶつかると衝突音がし、車が減速する
								//速い時に衝突で減速、遅い時の衝突は特に変化なし
								if (mCarSpeed > 6.5f){
									mCarSpeed = 2.0f;
									//mCarSpeed /= 2.0f;
									SoundCollision.Play();
									//激突時、エフェクト発生
									new CEffect(mPosition + CVector(0.0f,35.0f,0.0f), 100.0f, 100.0f, TextureExp, 4, 4, 1, 0);
								}
								else if (mCarSpeed > 4.0f){
									mCarSpeed = 2.0f;
									SoundCollisionSmall.Play();
									//軽くぶつけた時もエフェクト発生
									new CEffect(mPosition + CVector(0.0f, 15.5f, 0.0f), 60.0f, 60.0f, TextureHit, 3, 8,	1, 1);
								}
								else{
									//壁にこすりながらの移動時、速度が遅くなる
									if (mCarSpeed > 2.0f){
										mCarSpeed = 2.0f;
									}
								}
								//mCarSpeed = -mCarSpeed * 1.0;
								//mVelocityJump = 2.0f;
								
							}
							else if(yc->mpParent->mTag == CCharacter::EJUMPER){//ジャンプ台に接触した時
								//mVelocityJump = 0; 
								mVelocityJump = JUMPER01_POWER;
								mCanJump = true;
								SoundJump.Play();
							}
							else{
								mVelocityJump = 0;
								mCanJump = true;

								/*if (mRotation.mX < yc->mpParent->mRotation.mX){
								mRotation.mX++;
								}
								else if (mRotation.mX > yc->mpParent->mRotation.mX){
								mRotation.mX--;
								}*/

								/*１．斜面の法線ベクトルからY軸ベクトルを求めます。　済
									２．車体の進行方向から、Z軸ベクトルを求めます。  済??
									３．Y軸ベクトルとZ軸ベクトルの外積を計算し、X軸ベクトルを求めます。
									４．X軸ベクトルとY軸ベクトルの外積を計算し、Z軸ベクトルを求めます。
									５．Z軸ベクトルからX軸の回転値を求めます。              okか…？
									６．Z軸ベクトルからY軸の回転値を求めます。              okか…？
									７．X軸ベクトルとY軸ベクトルからZ軸の回転値を求めます。 okか…？
									８．求めた回転値を車体に適用します。                    okか…？*/
								CVector v[3], sv, ev;
								//各コライダの頂点をワールド座標へ変換
								v[0] = yc->mV[0] * yc->mMatrix * yc->mpParent->mMatrix;
								v[1] = yc->mV[1] * yc->mMatrix * yc->mpParent->mMatrix;
								v[2] = yc->mV[2] * yc->mMatrix * yc->mpParent->mMatrix;
								//面の法線を、外積を正規化して求める
								// 1.斜面の法線ベクトルからY軸ベクトルを求める
								CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();  //法線ベクトルは取れてるかも？
								// 2.車体の進行方向から、Z軸ベクトルを求める
								CVector preZvec = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
								// 3.Y軸ベクトルとZ軸ベクトルの外積を計算し、X軸ベクトルを求める
								CVector Xvec = (normal).Cross(preZvec).Normalize();
								// 4.X軸ベクトルとY軸ベクトルの外積を計算し、Z軸ベクトルを求める
								CVector Zvec = (Xvec).Cross(normal).Normalize();//？？？？？？？？？？？								
								// 5～7.回転値を求める
								float rad = asin(Zvec.mY);//5.
								float rotX = rad * 180 / PI * -1;//X軸は反転
								float rotY = atan2(Zvec.mX, Zvec.mZ) * 180 / PI;//6.
								float rotZ = atan2(Xvec.mY, normal.mY) * 180 / PI;//7.
								// 8.求めた回転値を車体に適用
								mRotation = CVector(rotX, rotY, rotZ);

								//int rotateofycmx = yc->mpParent->mRotation.mX;
								//rotateofycmx %= 360; //-360度から360度までの数値に変換
								////-235=125 300=-60 -180度未満か、180度以上の角度は
								//if (rotateofycmx < -180){
								//	rotateofycmx += 360;
								//}
								//else if (rotateofycmx >= 180){
								//	rotateofycmx -= 360;
								//}
								//mRotation.mX = rotateofycmx;
								//if (mRotation.mX < yc->mpParent->mRotation.mX){
								//	mRotation.mX = yc->mpParent->mRotation.mX;
								//}
								//else if (mRotation.mX > yc->mpParent->mRotation.mX){
								//	mRotation.mX = yc->mpParent->mRotation.mX;
								//}
								//mRotation = yc->mpParent->mRotation;
							}
						}
					}

				}
			}
			//自分のコライダが判定の時
			if (mc->mTag == CCollider::ESEARCH){
				//加速床に乗った時の処理
				if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
					CVector aiueo;//とりまベクトル
					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
						//mCarSpeed += 10.0f;
						//mCarSpeed = MAXSPEED+10.0f;						
						if (isBoost == false){
							SoundBoost.Play();
							new CEffect(mPosition + CVector(0.0f, 15.5f, 0.0f), 60.0f, 60.0f, TextureBoost, 3, 5, 1, 1);
						}
						isBoost = true;
						mBoostTime = 45;
					}
				}
			}

			

			
			/*if(yc->mpParent->mTag == CCharacter::ESPRING){
				mJumpV0 = 2.3f;
			}*/
			/*if (CItem::mpItem->mItemNumber == 2){
				mJumpV0 = 2.3f;
			}*/
		}
		if (yc->mType == CCollider::ESPHERE){
			if (CCollider::Collision(mc, yc)){
				if (yc->mpParent->mTag == CCharacter::ESPRING){
					mJumpV0 = 2.2f;
					SoundItemGet.Play();
				}
				if (yc->mpParent->mTag == CCharacter::ESCREW){
					mCanSwim = true;
					SoundItemGet.Play();
				}
				if (yc->mpParent->mTag == CCharacter::EKEY){
					mIsGetKey = true;
					SoundItemGet.Play();
				}
				if (yc->mpParent->mTag == CCharacter::EBOAT){//ボート乗船時
					mHaveBoat = true;
					mMoveSpeed = 0.85f;
				}


				if (mc->mTag == CCollider::EBODY){
					if (yc->mpParent->mTag == CCharacter::EENEMY){
						if (yc->mTag == CCollider::EBODY){
							CVector adjust;//調整用ベクトル
							////		//球同士の衝突判定
							if (CCollider::Collision(mc, yc, &adjust)){
								//位置の更新
								mPosition = mPosition - adjust * -1;
								//行列の更新
								CCharacter::Update();
								//printf("自分の衝突処理");
								//SoundCollisionSmall.Play();
							}
						}
					}
				}
				
			}
		}

		break;
	}

	////球コラと三角形の時
	//if (mc->mType == CCollider::ESPHERE && yc->mType == CCollider::ETRIANGLE){
	//	CVector adjust;//調整用ベクトル
	//	//コライダのmとyが衝突しているか判定
	//	//三角形と球の衝突判定
	//	if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
	//		//位置の更新
	//		mPosition = mPosition - adjust * -1;
	//		//行列の更新
	//		CCharacter::Update();
	//	}
	//}

}


void CPlayer::TaskCollision()
{
	mColBody.ChangePriority();
	mColTire.ChangePriority();
	//mColCamRange.ChangePriority();
	//mColCamera.ChangePriority();
	CollisionManager.Collision(&mColBody);
	CollisionManager.Collision(&mColTire);
	//CollisionManager.Collision(&mColCamRange);	
	//CollisionManager.Collision(&mColCamera);
}