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
		mpCollider[i].ChangePriority();
	}
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
}


void CRigidObj::TaskCollision()
{
	mColBody.ChangePriority();
	CollisionManager.Collision(&mColBody);
	mColBody2nd.ChangePriority();
	CollisionManager.Collision(&mColBody2nd);
}