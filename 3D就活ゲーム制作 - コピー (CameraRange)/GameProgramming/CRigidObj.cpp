#include "CRigidObj.h"
#include "CTaskManager.h"

CRigidObj *CRigidObj::mpRigObj = 0;

#define G (9.8f / 120.0f)//重力加速度//60.0f

//CRigidObj::CRigidObj()
////:mColBody(this, CVector(0.0f, 4.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f)
//{
//	mpRigObj = this;
//
//	//mScale = CVector(2.5f, 2.5f, 2.5f);
//	mVelocity = 0.0f;
//	mJumpPrio = 0;
//	//CanMove = false;
//
//	//mTag = EPLAYER;
//	//CCharacter::Update();
//
//	//mColBody.mTag = CCollider::EBODY;
//
//}


//コンストラクタ
//model:モデルのポインタ position:位置 rotation:回転 scale:拡縮
CRigidObj::CRigidObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:mpCollider(0)
, mColBody(this, CVector(0.0f, 0.0f - 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 21.0f)
, mColBody2nd(this, CVector(0.0f, 0.0f + 3.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 31.0f)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;

	mpRigObj = this;
	mVelocity = 0.0f;
	mJumpPrio = 0;

	CCharacter::Update();
	//モデルの三角形の数分、コライダの配列を作成します
	mpCollider = new CCollider[model->mTriangles.size()];
	for (int i = 0; i < model->mTriangles.size(); i++){
		//コライダを三角形コライダで設定していきます
		mpCollider[i].SetTriangle(this,
			model->mTriangles[i].mV[0],
			model->mTriangles[i].mV[1],
			model->mTriangles[i].mV[2]);
		//if (mObjNumber == 111){
		//	//加速床の当たり判定だけ上に移動させる
		//	model->mTriangles[i].mV[0] = model->mTriangles[i].mV[0] + CVector(0.0f, 5.0f, 0.0f);
		//	model->mTriangles[i].mV[1] = model->mTriangles[i].mV[1] + CVector(0.0f, 5.0f, 0.0f);
		//	model->mTriangles[i].mV[2] = model->mTriangles[i].mV[2] + CVector(0.0f, 5.0f, 0.0f);
		//}
		mpCollider[i].ChangePriority();
	}

	//if (mObjNumber == 99 || mObjNumber == 575){
	//	//当たり判定を生成しない
	//	//これにより当たり判定の数を増やすほど処理が重くなることが実証された
	//	//逆に当たり判定を増やさなければいいので、必要ない当たり判定はどんどんカットしていくよ。
	//}
	//else{
	//	CCharacter::Update();
	//	//モデルの三角形の数分、コライダの配列を作成します
	//	mpCollider = new CCollider[model->mTriangles.size()];
	//	for (int i = 0; i < model->mTriangles.size(); i++){
	//		//コライダを三角形コライダで設定していきます
	//		mpCollider[i].SetTriangle(this,
	//			model->mTriangles[i].mV[0],
	//			model->mTriangles[i].mV[1],
	//			model->mTriangles[i].mV[2]);
	//		//if (mObjNumber == 111){
	//		//	//加速床の当たり判定だけ上に移動させる
	//		//	model->mTriangles[i].mV[0] = model->mTriangles[i].mV[0] + CVector(0.0f, 5.0f, 0.0f);
	//		//	model->mTriangles[i].mV[1] = model->mTriangles[i].mV[1] + CVector(0.0f, 5.0f, 0.0f);
	//		//	model->mTriangles[i].mV[2] = model->mTriangles[i].mV[2] + CVector(0.0f, 5.0f, 0.0f);
	//		//}
	//		mpCollider[i].ChangePriority();
	//	}
	//}


	//mVelocity = 0.0f;

	//mEnabled = false;
}
//デストラクタ
CRigidObj::~CRigidObj(){
	//コライダがあれば削除
	if (mpCollider){
		//delete[] 配列を削除
		delete[] mpCollider;
	}
}

void CRigidObj::Update(){
	mPosition = CVector(0.0f, mVelocity*2.0f, 0.0f) * //mMatrixScale * 
		CMatrix().RotateZ(0) *
		CMatrix().RotateX(0) *
		CMatrix().RotateY(0)
		*mMatrixTranslate;
	CCharacter::Update();
	//転落してしまった時(Rキーで即リスタート)
	if (mPosition.mY < -150.0f){
		//落下の勢いを0にする
		mVelocity = 0.0f;
		mPosition.mY = 30.0f;
		CCharacter::Update();
	}	
	//重力の影響を反映する
	mVelocity -= G;

	if (mJumpPrio > 0){
		mJumpPrio--;
	}
}

void CRigidObj::Collision(CCollider *mc, CCollider *yc){
	//自身のコライダタイプの判定
	switch (mc->mType){
	case CCollider::ETRIANGLE://三角コライダ
		//相手のコライダも三角コライダの時
		if (yc->mType == CCollider::ETRIANGLE){
			mVelocity = 0;
		}
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (yc->mType == CCollider::ETRIANGLE){
			//自分自身と衝突するの禁止
			if (mc != yc){
				CVector aiueo;//とりまベクトル
				if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
					mVelocity = 1.0f;
				}
			}			
		}
	}


	////自身のコライダタイプの判定
	//switch (mc->mType){
	//case CCollider::ESPHERE://球コライダ
	//	//相手のコライダが三角コライダの時
	//	if (yc->mType == CCollider::ETRIANGLE){
	//		//自分のコライダが本体の時
	//		if (mc->mTag == CCollider::EBODY){
	//			//芝生通過中の処理
	//			if (yc->mpParent->mTag == CCharacter::EGRASS){
	//				CVector aiueo;//仮のベクトル
	//				if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
	//					
	//				}
	//			}
	//			
	//			if (mCanSwim && yc->mpParent->mTag == CCharacter::EWATER){
	//				//通過可能、ステージ1の水
	//			}
	//			else if (yc->mpParent->mTag == CCharacter::ECLEARWATER){
	//				//通過可能、ステージ2の水
	//			}
	//			else if (yc->mpParent->mTag == CCharacter::ECHECKPOINT
	//				|| yc->mpParent->mTag == CCharacter::ECHECKPOINT2
	//				|| yc->mpParent->mTag == CCharacter::ECHECKPOINT3
	//				|| yc->mpParent->mTag == CCharacter::EDASHBOARD){
	//				//処理は行われるが、これらのパネルは通過可能
	//			}
	//			else{
	//				if (mJumpPrio < 1){
	//					CVector adjust;//調整用ベクトル
	//					//		//三角形と球の衝突判定
	//					//		CCollider::CollisionTriangleSphere(yc, mc, &adjust);
	//					if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
	//						//位置の更新
	//						mPosition = mPosition - adjust * -1;
	//						//行列の更新
	//						CCharacter::Update();
	//						if (yc->mpParent->mTag == CCharacter::EWALL){
	//							//衝突したのが壁だった場合は壁には引っかからず落下
	//							//壁にぶつかると衝突音がし、車が減速する
	//							//速い時に衝突で減速、遅い時の衝突は特に変化なし
	//							if (mCarSpeed > 4.5f){
	//								mCarSpeed = 2.0f;
	//								//mCarSpeed /= 2.0f;
	//								SoundCollision.Play();
	//							}
	//							else if (mCarSpeed > 3.0f){
	//								mCarSpeed = 2.0f;
	//								SoundCollisionSmall.Play();
	//							}
	//							else{
	//								//壁にこすりながらの移動時、速度が遅くなる
	//								if (mCarSpeed > 2.0f){
	//									mCarSpeed = 2.0f;
	//								}
	//							}
	//						}
	//						else{
	//							mVelocityJump = 0;
	//							mCanJump = true;
	//							int rotateofycmx = yc->mpParent->mRotation.mX;
	//							rotateofycmx %= 360; //-360度から360度までの数値に変換
	//							//-235=125 300=-60 -180度未満か、180度以上の角度は
	//							if (rotateofycmx < -180){
	//								rotateofycmx += 360;
	//							}
	//							else if (rotateofycmx >= 180){
	//								rotateofycmx -= 360;
	//							}
	//							mRotation.mX = rotateofycmx;
	//						}
	//					}
	//				}
	//			}
	//		}
	//		//自分のコライダが判定の時
	//		if (mc->mTag == CCollider::ESEARCH){
	//			//加速床に乗った時の処理
	//			if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
	//				CVector aiueo;//とりまベクトル
	//				if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
	//					isBoost = true;
	//					mBoostTime = 45;
	//				}
	//			}
	//		}
	//	}
	//	if (yc->mType == CCollider::ESPHERE){
	//		if (CCollider::Collision(mc, yc)){
	//	
	//			if (mc->mTag == CCollider::EBODY){
	//				if (yc->mpParent->mTag == CCharacter::EENEMY){
	//					CVector adjust;//調整用ベクトル
	//					////		//球同士の衝突判定
	//					if (CCollider::Collision(mc, yc, &adjust)){
	//						//位置の更新
	//						mPosition = mPosition - adjust * -1;
	//						//行列の更新
	//						CCharacter::Update();
	//						//printf("自分の衝突処理");
	//						//SoundCollisionSmall.Play();
	//					}
	//				}
	//			}
	//		}
	//	}
	//	break;
	//}
}


void CRigidObj::TaskCollision()
{
	mColBody.ChangePriority();
	CollisionManager.Collision(&mColBody);
	mColBody2nd.ChangePriority();
	CollisionManager.Collision(&mColBody2nd);
}