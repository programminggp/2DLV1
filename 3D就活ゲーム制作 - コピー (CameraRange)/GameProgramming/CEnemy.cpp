#include "CEnemy.h"
#include "CKey.h"

#include "CItem.h"
#include "CBullet.h"
#include "CSceneTitle.h"

//乱数を実装するインクルード群
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//三角関数関連のインクルード
#include <math.h>
#define PI 3.141592

//衝突時のエフェクト追加
#include "CEffect.h"
extern std::shared_ptr<CTexture> TextureExp;
extern std::shared_ptr<CTexture> TextureHit;
extern std::shared_ptr<CTexture> TextureBoost;
#include "CTaskManager.h"

extern CSound SoundBoost;
extern CSound SoundEngine;
extern CSound SoundCollision;
extern CSound SoundCollisionSmall;

CEnemy *CEnemy::mpEnemy = 0;

#define G (9.8f / 90.0f)//重力加速度//60.0f
#define JUMPV0 (4.0f*4.0f)//ジャンプ初速//4.0f

#define MAXSPEED 20.0f //4.5f+3.0f//-0.5f//車の最高速度 //一応プレイヤーが追いつける程度に最高速は少し低め
#define MAXSPEED_BACK 1.0f*2 *2//車の後退する最大速度
#define CAR_POWER 0.05f*2 //*2//1フレーム辺りの車の加速していく量
#define CAR_BREAK_POWER 0.025f*2 *2//前進中のブレーキの強さ

#define DECELERATE 0.05f*2 //車の減速する量
#define FIX_ANGLE_VALUE 0.5f*2 //角度が0度に向けて調整される量(主にX・Z用)
#define JUMPER01_POWER 3.0f //ジャンプ台1でのジャンプ力
#define RESTART_TIME 30*60 //敵が詰まった時、一定時間経過でリスタートさせる

//旧速度設定
//#define MAXSPEED 7.0f //車の最高速度
//#define MAXSPEED_BACK 2.0f //車の後退する最大速度
//#define CAR_POWER 0.1f //1フレーム辺りの車の加速していく量
//#define CAR_BREAK_POWER 0.05f //前進中のブレーキの強さ
//#define DECELERATE 0.1f //車の減速する量
//#define FIX_ANGLE_VALUE 0.5f //角度が0度に向けて調整される量(主にX・Z用)

CEnemy::CEnemy()
//車体のY座標は0.0fにしたいんだけど・・・
//0.0fにしたら車体が浮いてるように見えてしまう
:mColBody(this, CVector(0.0f, 4.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 3)
, mColTire(this, CVector(0.0f, -16.0f + 15.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 3)
, mSearch(this, CVector(0.0f, 20.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 15)
{
	srand(time(NULL));

	mpEnemy = this;

	mScale = CVector(2.5f * 3, 2.5f * 3, 2.5f * 3);

	mVelocityJump = 0.0f;
	mJumpV0 = 1.1f;//バネ取得後は2.3fの予定
	mMoveSpeed = 0.5f;
	mADMoveX = 0.0f;  mWSMoveZ = 0.0f;
	mCarSpeed = 0.0f;//車の速度の初期化
	mTurnSpeed = 0.0f;

	mCPULevelSpeed = 0.0f;
	if (CSceneTitle::mDifficulty == 1){
		mCPULevelSpeed = 0.0f;
	}
	else if (CSceneTitle::mDifficulty == 2){
		mCPULevelSpeed = 0.0f;
	}
	else if (CSceneTitle::mDifficulty == 3){
		mCPULevelSpeed = 0.0f;
	}
	
	mCanJump = false;
	CanMove = false;

	mChecks = 0;

	isBoost = false;
	mBoostMaxSpeed = 0.0f;
	mBoostTime = 0;

	mTag = EENEMY;

	//スタート地点の座標を設定;
	mStartPoint[0] = 350.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = -100.0f;

	mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
	CCharacter::Update();

	mColBody.mTag = CCollider::EBODY;
	mColTire.mTag = CCollider::ESEARCH;
	mSearch.mTag = CCollider::ESEARCH;

	SoundBoost.Load("SE\\Shortbridge31-3.wav");
	SoundEngine.Load("SE\\SNES-Racing01-02.wav");
	SoundCollision.Load("SE\\bomb1.wav");
	SoundCollisionSmall.Load("SE\\SNES-Racing01-10(Collision).wav");

	isSoundEngine = false;
	
	mPointCnt = 0;//最初のポイントを設定
	mPointTime = 0;//現ポイントに移ってからの経過時間
	//mpPoint = &mPoint[mPointCnt];//目指すポイントのポインタを設定

	mpPoint = mPoint;
	mVPoint = mpPoint->mPosition;//一番最初は分散無し

	if (CSceneTitle::mDifficulty == 1){

	}
	else{

	}
	mMaxSpeed_PtoP = 20.0f;

	mRespawnCount = 0;
	mEnemyLap = 1;//敵のラップ数を１周目に設定する
	isTouchGoal = false;
	isEnemyGoaled = false;//まだゴールしてない状態にする
	mGoalTime = 0; mRank = 1;
}

void CEnemy::Update(){	
	//コース・ポインタ・AIの強さごとに最高速度を調整
	if (CSceneTitle::mMode == 2){
		if (mpPoint == mPoint){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint2){
			mMaxSpeed_PtoP = 10.0f;
		}
		else if (mpPoint == mPoint4){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint6){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint8){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint9){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint11){
			mMaxSpeed_PtoP = 14.0f;
		}
		else if (mpPoint == mPoint12){
			mMaxSpeed_PtoP = 13.0f;
		}
		else if (mpPoint == mPoint13){
			mMaxSpeed_PtoP = 10.0f;
		}
		else if (mpPoint == mPoint15){
			mMaxSpeed_PtoP = 18.0f;
		}
		else if (mpPoint == mPoint16){
			mMaxSpeed_PtoP = 14.0f;
		}
		else if (mpPoint == mPoint17){
			mMaxSpeed_PtoP = 15.0f;
		}
		else{
			mMaxSpeed_PtoP = 20.0f;
		}
	}
	else if (CSceneTitle::mMode == 5){
		if (mpPoint == mPoint){
			mMaxSpeed_PtoP = 19.0f;
		}
		else if (mpPoint == mPoint2){
			mMaxSpeed_PtoP = 17.0f;
		}
		else if (mpPoint == mPoint3){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint4){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint8){
			mMaxSpeed_PtoP = 16.0f;
		}
		else if (mpPoint == mPoint9){
			mMaxSpeed_PtoP = 9.5f;
		}
		else if (mpPoint == mPoint10){
			mMaxSpeed_PtoP = 17.0f;
		}
		else if (mpPoint == mPoint11){
			mMaxSpeed_PtoP = 11.0f;
		}
		else if (mpPoint == mPoint12){
			mMaxSpeed_PtoP = 12.0f;
		}
		else if (mpPoint == mPoint13){
			mMaxSpeed_PtoP = 14.0f;
		}
		else if (mpPoint == mPoint14){
			mMaxSpeed_PtoP = 14.0f;
		}
		else if (mpPoint == mPoint15){
			mMaxSpeed_PtoP = 13.0f;
		}
		else if (mpPoint == mPoint16){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint29){
			mMaxSpeed_PtoP = 10.0f;
		}
		else if (mpPoint == mPoint30){
			mMaxSpeed_PtoP = 5.0f;
		}
		else if (mpPoint == mPoint31){
			mMaxSpeed_PtoP = 5.0f;
		}
		else if (mpPoint == mPoint35){
			mMaxSpeed_PtoP = 19.0f;
		}
		else if (mpPoint == mPoint36){
			mMaxSpeed_PtoP = 18.0f;
		}
		else if (mpPoint == mPoint40){
			mMaxSpeed_PtoP = 16.0f;
		}
		else if (mpPoint == mPoint41){
			mMaxSpeed_PtoP = 13.0f;
		}
		else if (mpPoint == mPoint42){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint43){
			mMaxSpeed_PtoP = 12.5f;
		}

		else{
			mMaxSpeed_PtoP = 20.0f;
		}
	}
	else{
		mMaxSpeed_PtoP = 20.0f;
	}

	//速度調整
	//次のポイントから次の次のポイントへのベクトル
	CVector vNext = mpPoint->GetNextPoint()->mPosition - mpPoint->mPosition;
	//現在位置から次のポイントへのベクトル
	CVector vFoward = mpPoint->mPosition - mPosition;
	//内積から曲がり具合を求める(0:90°1.0：真っすぐ）
	float corve = vFoward.Normalize().Dot(vNext.Normalize());

	mMaxSpeed_PtoP = MAXSPEED * corve;

	if (mMaxSpeed_PtoP < 1.0f)
	{
		mMaxSpeed_PtoP = 1.0f;
	}


	//ポイントへのベクトルを求める
	CVector dir = mVPoint - mPosition;
	//左方向へのベクトルを求める
	CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);

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


	if (CKey::Push(VK_UP) && CanMove && mCarSpeed < mMaxSpeed_PtoP || mChecks >= 0 && CanMove && mCarSpeed < mMaxSpeed_PtoP){
		if (mCarSpeed < MAXSPEED + mBoostMaxSpeed){
			/*if (left.Dot(dir) > -5.0f && left.Dot(dir) < 5.0f){
				mCarSpeed += CAR_POWER;
			}*/
			mCarSpeed += CAR_POWER;
		}
	}
	/*else if (CKey::Push(VK_DOWN) && CanMove || left.Dot(dir) < -5.0f && CanMove || left.Dot(dir) > 5.0f && CanMove)*/
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

	//目的地が左側にあり、操作可能な時
	if (left.Dot(dir) > 0.0f && CanMove){ //ハンドルを左に！
		//mRotation.mY++;
		if (mTurnSpeed >= 0.0f&&mTurnSpeed<0.5f){
			mTurnSpeed = 0.5f;
		}
		if (mTurnSpeed < 0.0f){
			mTurnSpeed += 0.11f;
		}
		mTurnSpeed += 0.04f;
	}
	//あるいは目的地が右方面で、操作可能な時
	else if (left.Dot(dir) < 0.0f && CanMove){//ハンドルを右に！
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
			//SoundEngine.Repeat();
			isSoundEngine = true;
		}
	}
	//車が停止している時
	else if (mCarSpeed == 0.0f){
		//SoundEngine.Stop();
		isSoundEngine = false;
	}
	//車がバックしている時
	else if (mCarSpeed < 0.0f){
		if (isSoundEngine == false){
			//バックは違う音を鳴らす予定
			//SoundEngine.Repeat();
			isSoundEngine = true;
		}
	}
	//X,Z方向の移動とY軸方向(重力)の移動は別々に行う
	mPosition = CVector(mADMoveX, 0.0f, mWSMoveZ + mCarSpeed) * mMatrixRotate * mMatrixTranslate;
	CCharacter::Update();
	//常に地面に対して垂直に落下
	//mPosition = CVector(0.0f, mVelocityJump, 0.0f) * mMatrix;//できてない
	mPosition = CVector(0.0f, mVelocityJump*2.0f, 0.0f) * //mMatrixScale * 
		CMatrix().RotateZ(0) *
		CMatrix().RotateX(0) *
		CMatrix().RotateY(0)
		*mMatrixTranslate;//できてる？
	//mMatrix = mMatrixScale * mMatrixRotate * mMatrixTranslate;

	//コースアウトした時、もしくは敵が壁等に引っかかり進めなくなっている時
	if (mPosition.mY < -700.0f || mPointTime > RESTART_TIME){
		mPointTime = 0;
		//落下の勢いを0にする
		mVelocityJump = 0.0f;
		//車の速度を0に
		mCarSpeed = 0.0f;
		mRotation = CVector(0.0f, 0.0f, 0.0f);
		if (CSceneTitle::mMode == 1){
			if (mChecks == 0){
				//スタートした時の位置、方向に戻される
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mRotation.mY = 0.0f;
				mpPoint = mPoint;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 1){
				mPosition = CVector(-80.0f, mStartPoint[1], 2175.0f);
				mRotation.mY = -55.0f;
				mpPoint = mPoint3;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1620.0f, mStartPoint[1], 450.0f);
				mRotation.mY = -175.0f;
				mpPoint = mPoint4;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 3){
				/*mPosition = CVector(-1412.0f, mStartPoint[1], -1720.0f);
				mRotation.mY = 120.0f;
				mpPoint = mPoint5;
				mVPoint = mpPoint->mPosition;*/
				mPosition = CVector(-1620.0f, mStartPoint[1], -250.0f);
				mRotation.mY = -175.0f;
				mpPoint = mPoint4;
				mVPoint = mpPoint->mPosition;
			}
		}
		else if (CSceneTitle::mMode == 2){
			if (mChecks == 0){
				//スタートした時の位置、方向に戻される
				mPosition = CVector(2222.0f, -13.538f, -2510.0f - 30.0f);
				mRotation.mY = 0.0f;
				//目標地点も戻る
				mpPoint = mPoint;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 1){
				mPosition = CVector(2893.0f, mStartPoint[1], 2473.0f);
				mRotation.mY = -59.0f;
				mpPoint = mPoint5;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1020.0f, mStartPoint[1], 4594.0f);
				mRotation.mY = -506.4f;
				mpPoint = mPoint10;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 3){
				mPosition = CVector(-1357.0f, mStartPoint[1] - 30.0f, -520.0f);
				mRotation.mY = -200.0f+40.0f;
				mpPoint = mPoint14;
				mVPoint = mpPoint->mPosition;
			}
		}
		else if (CSceneTitle::mMode == 3){
			if (mChecks == 0){
				//スタートした時の位置、方向に戻される
				mPosition = CVector(0.0f, -13.538f, 80.0f);
				mRotation.mY = 90.0f;
				//目標地点も戻る
				mpPoint = mPoint;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 1){
				mPosition = CVector(1127.4f, mStartPoint[1]+100.0f, -5054.0f);
				mRotation.mY = 270.1f;
				mpPoint = mPoint7;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 2){
				/*mPosition = CVector(777.0f, mStartPoint[1], 1925.0f);
				mStartRotation = 405.1f;*/
				mPosition = CVector(777.0f, mStartPoint[1], 1925.0f);
				mRotation.mY = 405.1f;
				mpPoint = mPoint12;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 3){
				mPosition = CVector(-5861.0f, mStartPoint[1], 1165.0f);
				mRotation.mY = -583.5f;
				mpPoint = mPoint20;
				mVPoint = mpPoint->mPosition;
			}
		}
		else if (CSceneTitle::mMode == 5){
			if (mChecks == 0){
				//スタートした時の位置、方向に戻される
				mPosition = CVector(-3755.5f, 13.5f, 16060.5f);
				mRotation.mY = -145.0f;
				//目標地点も戻る
				mpPoint = mPoint;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 1){
				mPosition = CVector(-16054.4f, 4915.0f, -2180.0f);
				mRotation.mY = -174.6f;
				mpPoint = mPoint21;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 2){
				mPosition = CVector(4680.0f, 13.5f, -2027.0f);
				mRotation.mY = 147.2f;
				mpPoint = mPoint32;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 3){
				mPosition = CVector(14809.0f, 13.5f, 4270.0f);
				mRotation.mY = -9.5f;
				mpPoint = mPoint38;
				mVPoint = mpPoint->mPosition;
			}
		}
		else{
			if (mChecks == 0){
				//スタートした時の位置、方向に戻される
				mPosition = CVector(mStartPoint[0]-300.0f, mStartPoint[1]+400.0f, mStartPoint[2]-0.0f);
				mRotation.mY = 0.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(-80.0f, mStartPoint[1], 2175.0f);
				mRotation.mY = -55.0f;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1620.0f, mStartPoint[1], 450.0f);
				mRotation.mY = -175.0f;
			}
			else if (mChecks == 3){
				mPosition = CVector(-1212.0f, mStartPoint[1], -1616.0f);
				mRotation.mY = 120.0f;
			}
		}		
	}
	CCharacter::Update();

	//重力の影響を反映する
	mVelocityJump -= G;
	
	if (CKey::Push('I')){
		mpPoint->mRotation.mY++;
	}	
}

void CEnemy::Collision(CCollider *mc, CCollider *yc){
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
									mCarSpeed = 3.2f + 1.8f;
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
							//mChecks = 0;
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
				if (yc->mpParent->mTag == CCharacter::EGOALPOINT){//ゴール地点
					if (mChecks == 3){
						//各中間地点を通過していなければ1周判定がなされない
						CVector aiu;//数合わせのためだけのベクトル
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							isTouchGoal = true;
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::EWATER){
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
					//これらのタグが付いたオブジェクトは通過可能
				}
				else{
					CVector adjust;//調整用ベクトル
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
								//SoundCollision.Play();
								//激突時、エフェクト発生
								new CEffect(mPosition + CVector(0.0f, 35.0f, 0.0f), 100.0f, 100.0f, TextureExp, 4, 4, 1, 0);
							}
							else if (mCarSpeed > 4.0f){
								mCarSpeed = 2.0f;
								//SoundCollisionSmall.Play();
								//軽くぶつけた時もエフェクト発生
								new CEffect(mPosition + CVector(0.0f, 15.5f, 0.0f), 60.0f, 60.0f, TextureHit, 3, 8, 1, 1);
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
						else if (yc->mpParent->mTag == CCharacter::EJUMPER){//ジャンプ台に接触した時
							//mVelocityJump = 0; 
							mVelocityJump = JUMPER01_POWER;
							mCanJump = true;
							//SoundJump.Play();
						}
						else{
							mVelocityJump = 0;
							mCanJump = true;
							mRotation = CCollider::CalculateEulerAngle(mc, yc, mMatrixRotate, PI);
						}
					}
					

				}
			}
			//自分のコライダが索敵コライダの時
			if (mc->mTag == CCollider::ESEARCH){
				//加速床に乗った時の処理
				if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
					CVector aiueo;//とりまベクトル
					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
						if (isBoost == false){
							new CEffect(mPosition + CVector(0.0f, 15.5f, 0.0f), 60.0f, 60.0f, TextureBoost, 3, 5, 1, 1);
						}
						isBoost = true;
						mBoostTime = 45;
					}
				}
			}
		}
		if (yc->mType == CCollider::ESPHERE){
			if (CCollider::Collision(mc, yc)){
				//
				if (mc->mTag == CCollider::EBODY){
					if (yc->mpParent->mTag == CCharacter::EPLAYER
						&& yc->mTag == CCollider::EBODY){
						CVector adjust;//調整用ベクトル
						////		//球同士の衝突判定
						if (CCollider::Collision(mc, yc, &adjust)){
							//位置の更新
							mPosition = mPosition - adjust * -1;
							//行列の更新
							CCharacter::Update();
						}
					}
					
					if (yc->mpParent->mTag == CCharacter::EENEMY
						&& yc->mTag == CCollider::EBODY){
						if (mc == yc){
							return;
						}
						CVector adjust;//調整用ベクトル
						////		//球同士の衝突判定
						if (CCollider::Collision(mc, yc, &adjust)){
							//位置の更新
							mPosition = mPosition - adjust * -1;
							//行列の更新
							CCharacter::Update();
						}
					}					
				}
				//
				if (mc->mTag == CCollider::ESEARCH){
					//ポインタからポインタに向けて移動する
					if (yc->mpParent->mTag == CCharacter::EPOINT){
						CVector adjust;//調整用ベクトル
						//		//球同士の衝突判定
						if (CCollider::Collision(mc, yc, &adjust)){
							//衝突したポインタと目指しているポインタが同じ時
							if (yc->mpParent == mpPoint){
								//ポイント経過時間のリセット
								mPointTime = 0;
								//とりあえず先にint付けで生成しておく
								int r = (mc->mRadius + yc->mRadius) * 0.8f;
								int gap = (rand() % (r * 2) - r);
								//敵AIのLvにより分散値も変化
								if (CSceneTitle::mDifficulty == 1){
									r = (mc->mRadius + yc->mRadius) * 0.5f;
									gap = (rand() % (r * 2) - r);
								}
								else if (CSceneTitle::mDifficulty == 2){
									r = (mc->mRadius + yc->mRadius) * 0.4f;
									gap = (rand() % (r * 2) - r);
								}
								else if (CSceneTitle::mDifficulty == 3){
									r = (mc->mRadius + yc->mRadius) * 0.2f;
									gap = (rand() % (r * 2) - r);
								}

								//コース5は分散無しの地点あり
								if (CSceneTitle::mMode == 5){
									mpPoint = mpPoint->GetNextPoint();
									mVPoint = mpPoint->mPosition;
									return;

									//次のポイントのポインタを設定
									if (mpPoint == mPoint){
										mVPoint = mPoint2->mPosition;
										mpPoint = mPoint2;
									}
									else if (mpPoint == mPoint2){
										mVPoint = mPoint3->mPosition;
										mpPoint = mPoint3;
									}
									else if (mpPoint == mPoint3){
										mVPoint = mPoint4->mPosition;
										mpPoint = mPoint4;
									}
									else if (mpPoint == mPoint4){
										mVPoint = mPoint5->mPosition;
										mpPoint = mPoint5;
									}
									else if (mpPoint == mPoint5){
										mVPoint = mPoint6->mPosition;
										mpPoint = mPoint6;
									}
									else if (mpPoint == mPoint6){
										mVPoint = mPoint7->mPosition;
										mpPoint = mPoint7;
									}
									else if (mpPoint == mPoint7){
										mVPoint = mPoint8->mPosition;
										mpPoint = mPoint8;
									}
									else if (mpPoint == mPoint8){
										mVPoint = mPoint9->mPosition;
										mpPoint = mPoint9;
									}
									else if (mpPoint == mPoint9){
										mVPoint = mPoint10->mPosition;
										mpPoint = mPoint10;
									}
									else if (mpPoint == mPoint10){
										mVPoint = mPoint11->mPosition;
										mpPoint = mPoint11;
									}
									else if (mpPoint == mPoint11){
										mVPoint = mPoint12->mPosition;
										mpPoint = mPoint12;
									}
									else if (mpPoint == mPoint12){
										mVPoint = mPoint13->mPosition;
										mpPoint = mPoint13;
									}
									else if (mpPoint == mPoint13){
										mVPoint = mPoint14->mPosition;
										mpPoint = mPoint14;
									}
									else if (mpPoint == mPoint14){
										mVPoint = mPoint15->mPosition;
										mpPoint = mPoint15;
									}
									else if (mpPoint == mPoint15){
										mVPoint = mPoint16->mPosition;
										mpPoint = mPoint16;
									}
									else if (mpPoint == mPoint16){
										mVPoint = mPoint17->mPosition;
										mpPoint = mPoint17;
									}
									else if (mpPoint == mPoint17){
										mVPoint = mPoint18->mPosition;
										mpPoint = mPoint18;
									}
									else if (mpPoint == mPoint18){
										mVPoint = mPoint19->mPosition;
										mpPoint = mPoint19;
									}
									else if (mpPoint == mPoint19){
										mVPoint = mPoint20->mPosition;
										mpPoint = mPoint20;
									}
									else if (mpPoint == mPoint20){
										mVPoint = mPoint21->mPosition;
										mpPoint = mPoint21;
									}
									else if (mpPoint == mPoint21){
										mVPoint = mPoint22->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint22;
									}
									else if (mpPoint == mPoint22){
										mVPoint = mPoint23->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint23;
									}
									else if (mpPoint == mPoint23){
										mVPoint = mPoint24->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint24;
									}
									else if (mpPoint == mPoint24){
										mVPoint = mPoint25->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint25;
									}
									else if (mpPoint == mPoint25){
										mVPoint = mPoint26->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint26;
									}
									else if (mpPoint == mPoint26){
										mVPoint = mPoint27->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint27;
									}
									else if (mpPoint == mPoint27){
										mVPoint = mPoint28->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint28;
									}
									else if (mpPoint == mPoint28){
										mVPoint = mPoint29->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint29;
									}
									else if (mpPoint == mPoint29){
										mVPoint = mPoint30->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint30;
									}
									else if (mpPoint == mPoint30){
										mVPoint = mPoint31->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint31;
									}
									else if (mpPoint == mPoint31){
										mVPoint = mPoint32->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint32;
									}
									else if (mpPoint == mPoint32){
										mVPoint = mPoint33->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint33;
									}
									else if (mpPoint == mPoint33){
										mVPoint = mPoint34->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint34;
									}
									else if (mpPoint == mPoint34){
										mVPoint = mPoint35->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint35;
									}
									else if (mpPoint == mPoint35){
										mVPoint = mPoint36->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint36;
									}
									else if (mpPoint == mPoint36){
										mVPoint = mPoint37->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint37;
									}
									else if (mpPoint == mPoint37){
										mVPoint = mPoint38->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint38;
									}
									else if (mpPoint == mPoint38){
										mVPoint = mPoint39->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint39;
									}
									else if (mpPoint == mPoint39){
										mVPoint = mPoint40->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint40;
									}
									else if (mpPoint == mPoint40){
										mVPoint = mPoint41->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint41;
									}
									else if (mpPoint == mPoint41){
										mVPoint = mPoint42->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint42;
									}
									else if (mpPoint == mPoint42){
										mVPoint = mPoint43->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint43;
									}
									else if (mpPoint == mPoint43){
										mVPoint = mPoint44->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint44;
									}
									else if (mpPoint == mPoint44){
										mVPoint = mPoint45->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint45;
									}
									else if (mpPoint == mPoint45){
										mVPoint = mPoint46->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint46;
									}
									else if (mpPoint == mPoint46){
										mVPoint = mPoint47->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint47;
									}
									else if (mpPoint == mPoint47){
										mVPoint = mPoint48->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint48;
									}
									else if (mpPoint == mPoint48){
										mVPoint = mPoint49->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint49;
									}
									else if (mpPoint == mPoint49){
										mVPoint = mPoint50->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint50;
									}
									else if (mpPoint == mPoint50){
										mVPoint = mPoint51->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint51;
									}
									else if (mpPoint == mPoint51){
										mVPoint = mPoint52->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint52;
									}
									else if (mpPoint == mPoint52){
										mVPoint = mPoint53->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint53;
									}
									else if (mpPoint == mPoint53){
										mVPoint = mPoint54->mPosition;
										mpPoint = mPoint54;
									}
									else if (mpPoint == mPoint54){
										mVPoint = mPoint->mPosition;
										mpPoint = mPoint;
									}
								}
								else{
									//次のポイントのポインタを設定
									if (mpPoint == mPoint){
										mVPoint = mPoint2->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint2;
									}
									else if (mpPoint == mPoint2){
										mVPoint = mPoint3->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint3;
									}
									else if (mpPoint == mPoint3){
										mVPoint = mPoint4->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint4;
									}
									else if (mpPoint == mPoint4){
										mVPoint = mPoint5->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint5;
									}
									else if (mpPoint == mPoint5){
										mVPoint = mPoint6->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint6;
									}
									else if (mpPoint == mPoint6){
										mVPoint = mPoint7->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint7;
									}
									else if (mpPoint == mPoint7){
										mVPoint = mPoint8->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint8;
									}
									else if (mpPoint == mPoint8){
										mVPoint = mPoint9->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint9;
									}
									else if (mpPoint == mPoint9){
										mVPoint = mPoint10->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint10;
									}
									else if (mpPoint == mPoint10){
										mVPoint = mPoint11->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint11;
									}
									else if (mpPoint == mPoint11){
										mVPoint = mPoint12->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint12;
									}
									else if (mpPoint == mPoint12){
										//コース2or3を走行中かで分岐する
										if (CSceneTitle::mMode == 2 || CSceneTitle::mMode == 3 || CSceneTitle::mMode == 5){
											mVPoint = mPoint13->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint13;
										}
										else{
											mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint;//ポイント1に戻ってループする
										}
									}
									//コース2
									else if (CSceneTitle::mMode == 2){
										if (mpPoint == mPoint13){
											mVPoint = mPoint14->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint14;
										}
										else if (mpPoint == mPoint14){
											mVPoint = mPoint15->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint15;
										}
										else if (mpPoint == mPoint15){
											mVPoint = mPoint16->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint16;
										}
										else if (mpPoint == mPoint16){
											mVPoint = mPoint17->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint17;
										}
										else if (mpPoint == mPoint17){
											mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint;
										}
									}
									//コース3ではポインタの数が拡張される
									else if (CSceneTitle::mMode == 3){
										if (mpPoint == mPoint13){
											mVPoint = mPoint14->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint14;
										}
										else if (mpPoint == mPoint14){
											mVPoint = mPoint15->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint15;
										}
										else if (mpPoint == mPoint15){
											mVPoint = mPoint16->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint16;
										}
										else if (mpPoint == mPoint16){
											mVPoint = mPoint17->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint17;
										}
										else if (mpPoint == mPoint17){
											mVPoint = mPoint18->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint18;
										}
										else if (mpPoint == mPoint18){
											mVPoint = mPoint19->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint19;
										}
										else if (mpPoint == mPoint19){
											mVPoint = mPoint20->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint20;
										}
										else if (mpPoint == mPoint20){
											mVPoint = mPoint21->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint21;
										}
										else if (mpPoint == mPoint21){
											mVPoint = mPoint22->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint22;
										}
										else if (mpPoint == mPoint22){
											mVPoint = mPoint23->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint23;
										}
										else if (mpPoint == mPoint23){
											mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint;
										}
									}
									//コース5ではポインタの数が拡張される
									else if (CSceneTitle::mMode == 5){
										if (mpPoint == mPoint13){
											mVPoint = mPoint14->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint14;
										}
										else if (mpPoint == mPoint14){
											mVPoint = mPoint15->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint15;
										}
										else if (mpPoint == mPoint15){
											mVPoint = mPoint16->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint16;
										}
										else if (mpPoint == mPoint16){
											mVPoint = mPoint17->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint17;
										}
										else if (mpPoint == mPoint17){
											mVPoint = mPoint18->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint18;
										}
										else if (mpPoint == mPoint18){
											mVPoint = mPoint19->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint19;
										}
										else if (mpPoint == mPoint19){
											mVPoint = mPoint20->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint20;
										}
										else if (mpPoint == mPoint20){
											mVPoint = mPoint21->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint21;
										}
										else if (mpPoint == mPoint21){
											mVPoint = mPoint22->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint22;
										}
										else if (mpPoint == mPoint22){
											mVPoint = mPoint23->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint23;
										}
										else if (mpPoint == mPoint23){
											mVPoint = mPoint24->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint24;
										}
										else if (mpPoint == mPoint24){
											mVPoint = mPoint25->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint25;
										}
										else if (mpPoint == mPoint25){
											mVPoint = mPoint26->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint26;
										}
										else if (mpPoint == mPoint26){
											mVPoint = mPoint27->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint27;
										}
										else if (mpPoint == mPoint27){
											mVPoint = mPoint28->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint28;
										}
										else if (mpPoint == mPoint28){
											mVPoint = mPoint29->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint29;
										}
										else if (mpPoint == mPoint29){
											mVPoint = mPoint30->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint30;
										}
										else if (mpPoint == mPoint30){
											mVPoint = mPoint31->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint31;
										}
										else if (mpPoint == mPoint31){
											mVPoint = mPoint32->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint32;
										}
										else if (mpPoint == mPoint32){
											mVPoint = mPoint33->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint33;
										}
										else if (mpPoint == mPoint33){
											mVPoint = mPoint34->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint34;
										}
										else if (mpPoint == mPoint34){
											mVPoint = mPoint35->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint35;
										}
										else if (mpPoint == mPoint35){
											mVPoint = mPoint36->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint36;
										}
										else if (mpPoint == mPoint36){
											mVPoint = mPoint37->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint37;
										}
										else if (mpPoint == mPoint37){
											mVPoint = mPoint38->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint38;
										}
										else if (mpPoint == mPoint38){
											mVPoint = mPoint39->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint39;
										}
										else if (mpPoint == mPoint39){
											mVPoint = mPoint40->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint40;
										}
										else if (mpPoint == mPoint40){
											mVPoint = mPoint41->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint41;
										}

										else if (mpPoint == mPoint41){
											mVPoint = mPoint42->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint42;
										}
										else if (mpPoint == mPoint42){
											mVPoint = mPoint43->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint43;
										}
										else if (mpPoint == mPoint43){
											mVPoint = mPoint44->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint44;
										}
										else if (mpPoint == mPoint44){
											mVPoint = mPoint45->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint45;
										}
										else if (mpPoint == mPoint45){
											mVPoint = mPoint46->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint46;
										}
										else if (mpPoint == mPoint46){
											mVPoint = mPoint47->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint47;
										}
										else if (mpPoint == mPoint47){
											mVPoint = mPoint48->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint48;
										}
										else if (mpPoint == mPoint48){
											mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
											mpPoint = mPoint;
										}
									}
								}								
							}
						}
					}
				}
			}
		}
		break;
	}
}

void CEnemy::TaskCollision()
{
	mColBody.ChangePriority();
	mColTire.ChangePriority();
	mSearch.ChangePriority();
	CollisionManager.Collision(&mColBody);
	CollisionManager.Collision(&mColTire);
	CollisionManager.Collision(&mSearch);
}

//誘導ポイント
CPoint *CEnemy::mPoint;
CPoint *CEnemy::mPoint2;
CPoint *CEnemy::mPoint3;
CPoint *CEnemy::mPoint4;
CPoint *CEnemy::mPoint5;
CPoint *CEnemy::mPoint6;
CPoint *CEnemy::mPoint7;
CPoint *CEnemy::mPoint8;
CPoint *CEnemy::mPoint9;
CPoint *CEnemy::mPoint10;
CPoint *CEnemy::mPoint11;
CPoint *CEnemy::mPoint12;
CPoint *CEnemy::mPoint13;
CPoint *CEnemy::mPoint14;
CPoint *CEnemy::mPoint15;
CPoint *CEnemy::mPoint16;
CPoint *CEnemy::mPoint17;
CPoint *CEnemy::mPoint18;
CPoint *CEnemy::mPoint19;
CPoint *CEnemy::mPoint20;
CPoint *CEnemy::mPoint21;
CPoint *CEnemy::mPoint22;
CPoint *CEnemy::mPoint23;
CPoint *CEnemy::mPoint24;
CPoint *CEnemy::mPoint25;
CPoint *CEnemy::mPoint26;
CPoint *CEnemy::mPoint27;
CPoint *CEnemy::mPoint28;
CPoint *CEnemy::mPoint29;
CPoint *CEnemy::mPoint30;
CPoint *CEnemy::mPoint31;
CPoint *CEnemy::mPoint32;
CPoint *CEnemy::mPoint33;
CPoint *CEnemy::mPoint34;
CPoint *CEnemy::mPoint35;
CPoint *CEnemy::mPoint36;
CPoint *CEnemy::mPoint37;
CPoint *CEnemy::mPoint38;
CPoint *CEnemy::mPoint39;
CPoint *CEnemy::mPoint40;
CPoint *CEnemy::mPoint41;
CPoint *CEnemy::mPoint42;
CPoint *CEnemy::mPoint43;
CPoint *CEnemy::mPoint44;
CPoint *CEnemy::mPoint45;
CPoint *CEnemy::mPoint46;
CPoint *CEnemy::mPoint47;
CPoint *CEnemy::mPoint48;
CPoint *CEnemy::mPoint49;
CPoint *CEnemy::mPoint50;
CPoint *CEnemy::mPoint51;
CPoint *CEnemy::mPoint52;
CPoint *CEnemy::mPoint53;
CPoint *CEnemy::mPoint54;