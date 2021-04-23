#include "CCameraPos.h"
//#include "CKey.h"

#include "CItem.h"
#include "CSceneTitle.h"

#include "CTaskManager.h"

#include <stdio.h>
#include <math.h>

#define PI 3.141592

CCameraPos *CCameraPos::mpCamera = 0;

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


CCameraPos::CCameraPos()
//車体のY座標は0.0fにしたいんだけど・・・
//0.0fにしたら車体が浮いてるように見えてしまう
:mColCam(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 3)
{
	mpCamera = this;	

	CanMove = false;	
	mTag = EPLAYER;

	CCharacter::Update();

	mColCam.mTag = CCollider::ECAMERA;

//	mPosition = CPlayer::mpPlayer->mPosition;
	mPosition = CCameraRange::mpCameraRange->mPosition;

	mRotation = CPlayer::mpPlayer->mRotation;
	CCharacter::Update();
	mVCamY = 0;

}

void CCameraPos::Update(){	
	
	mVPoint = CCameraRange::mpCameraRange->mPosition;
	//mPosition.mY = CCameraRange::mpCameraRange->mPosition.mY;
	//mRotation = CPlayer::mpPlayer->mRotation;
	CCharacter::Update();
	//ポイントへのベクトルを求める
	CVector dir = mVPoint - mPosition;
	//左方向へのベクトルを求める
	CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	CVector up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
	while (left.Dot(dir) > 0.0f){
		mRotation.mY++;
		left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	}
	while (left.Dot(dir) < 0.0f){
		mRotation.mY--;
		left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	}
	//
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
	//mPosition = CVector(0.0f, 0.0f, mCameraSpeed) * CCameraRange::mpCameraRange->mMatrixRotate * CCameraRange::mpCameraRange->mMatrixTranslate;  // * mMatrixRotate * mMatrixTranslate;
	CCharacter::Update();
}

void CCameraPos::Collision(CCollider *mc, CCollider *yc){
	//自身のコライダタイプの判定
	switch (mc->mType){
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (yc->mType == CCollider::ETRIANGLE){
			//自分のコライダが本体の時
			if (mc->mTag == CCollider::ECAMERA){				
				//else{ 以外は通過可能
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
					//処理は行われるが、これらのパネルは通過可能
				}
				else{
					CVector adjust;//調整用ベクトル
					//		//三角形と球の衝突判定
					if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
						//位置の更新
						mPosition = mPosition - adjust * -1;
						//行列の更新
						CCharacter::Update();
						//printf("カメラ激突\n");
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