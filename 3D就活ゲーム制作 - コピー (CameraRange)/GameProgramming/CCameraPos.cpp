//#include "CSceneTitle.h"
#include "CCameraPos.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CCameraRange.h"

#include <stdio.h>
#include <math.h>

#define CAMERA_DISTANCE (302.0f)
#define ZOOMSPEED 4.0f //レースOPでカメラがズームする速度
#define ZOOM_SPENDTIME 5.0f*60 //OPでズーム演出にかける時間 

CCameraPos *CCameraPos::mpCamera = 0;


CCameraPos::CCameraPos()
:mColCam(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 3)
{
	mpCamera = this;	

	//CanMove = false;	
	mTag = EPLAYER;

	CCharacter::Update();

	mColCam.mTag = CCollider::ECAMERA;

	mPosition = CPlayer::mpPlayer->mPosition;
	mPosition = CCameraRange::mpCameraRange->mPosition;
	//printf("X:%f\nY:%f\nZ:%f\n", mPosition.mX, mPosition.mY, mPosition.mZ);
	mRotation = CPlayer::mpPlayer->mRotation;
	CCharacter::Update();
	mZoom_distance = ZOOMSPEED * ZOOM_SPENDTIME;
}

void CCameraPos::Update(){	
	CVector mVPoint = CCameraRange::mpCameraRange->mPosition;
	CCharacter::Update();
	//ポイントへのベクトルを求める
	CVector dir = mVPoint - mPosition;
	//左方向へのベクトルを求める
	CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	CVector up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
	//左方向
	while (left.Dot(dir) > 0.0f){
		mRotation.mY++;
		left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	}
	while (left.Dot(dir) < 0.0f){
		mRotation.mY--;
		left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	}
	//上方向
	while (up.Dot(dir) > 0.0f){
		mRotation.mX--;
		up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
	}
	while (up.Dot(dir) < 0.0f){
		mRotation.mX++;
		up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
	}
	CCharacter::Update();
	//プレイヤーの車のスピードを絶対値に変化
	mCameraSpeed = CPlayer::mpPlayer->mCarSpeed;
	if (mCameraSpeed < 0.0f){
		mCameraSpeed *= -1;
	}
	mPosition = CVector(0.0f, 0.0f, mCameraSpeed) * mMatrixRotate * mMatrixTranslate;
	CCharacter::Update();

	if (mZoom_distance < ZOOMSPEED && mZoom_distance > -ZOOMSPEED){
		mZoom_distance = 0.0f;
	}
	if (mZoom_distance > 0.0f){
		mZoom_distance -= ZOOMSPEED;
	}
	else if (mZoom_distance < 0.0f){
		mZoom_distance += ZOOMSPEED;
	}	
	
	//カメラとプレイヤーの距離を一定にする
	dir = (mPosition - CPlayer::mpPlayer->mPosition).Normalize() * ((CAMERA_DISTANCE) + mZoom_distance);
	mPosition = CPlayer::mpPlayer->mPosition + dir;	
	CCharacter::Update();

	//プレイヤーでリスポーンフラグが建った時の処理
	if (CPlayer::mpPlayer->isRespawn){
		mPosition = CVector(0.0f, 15.0f, -35.0f) * CPlayer::mpPlayer->mMatrixScale * CPlayer::mpPlayer->mMatrixRotate * CPlayer::mpPlayer->mMatrixTranslate;
		CCharacter::Update();
		CPlayer::mpPlayer->isRespawn = false;//フラグ消去
	}
}

void CCameraPos::Collision(CCollider *mc, CCollider *yc){
	//自身のコライダタイプの判定
	switch (mc->mType){
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (yc->mType == CCollider::ETRIANGLE){
			//自分のコライダが本体の時
			if (mc->mTag == CCollider::ECAMERA){
				if (yc->mpParent->mTag == CCharacter::EWATER
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT2
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT3
					|| yc->mpParent->mTag == CCharacter::EGOALPOINT					
					|| yc->mpParent->mTag == CCharacter::EDASHBOARD){
					//これらのパネルは通行可能
				}
				else{
					CVector adjust;//調整用ベクトル
					//		//三角形と球の衝突判定
					if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
						//位置の更新
						mPosition = mPosition - adjust * -1;
						//行列の更新
						CCharacter::Update();
					}
				}
			}
		}
		break;
	}
}


void CCameraPos::TaskCollision()
{
	mColCam.ChangePriority();
	CollisionManager.Collision(&mColCam);
}