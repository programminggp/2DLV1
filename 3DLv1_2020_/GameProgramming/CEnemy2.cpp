#include "CEnemy2.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CPlayer.h"

#define OBJ "f16.obj"	//モデルのファイル
#define MTL "f16.mtl"	//モデルのマテリアルファイル

CModel CEnemy2::mModel;	//モデルデータ作成

CEnemy2::CEnemy2()
: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
{
	//モデルが無いときは読み込む
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &mModel;
}


//コンストラクタ
//CEnemy(位置, 回転, 拡縮)
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale)
	: CEnemy2()
{
	//位置、回転、拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	CTransform::Update();	//行列の更新
	//優先度を1に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //削除して
	CTaskManager::Get()->Add(this); //追加する
}

//更新処理
void CEnemy2::Update() {
	return;
	//行列を更新
	CTransform::Update();
	//位置を移動
	mPosition = CVector(0.0f, 0.0f, 0.95f) * mMatrix;
	//
//	CVector dir = *mpTarget - mPosition;
	CVector dir =  mPosition;
	CVector left = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	CVector top = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	if (left.Dot(dir) > 0.0f)
	{
		mRotation.mY += 0.75f;
	}
	else
	{
		mRotation.mY -= 0.75f;
	}
	if (top.Dot(dir) > 0.0f)
	{
		mRotation.mX -= 0.75f;
	}
	else
	{
		mRotation.mX += 0.75f;
	}

}
//衝突処理
//Collision(コライダ1, コライダ2)
void CEnemy2::Collision(CCollider *m, CCollider *o) {
	//相手のコライダタイプの判定
	switch (o->mType)
	{
	case CCollider::ESPHERE: //球コライダの時
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//衝突している時は無効にする
			//mEnabled = false;
		}
		break;
	case CCollider::ETRIANGLE: //三角コライダの時
		CVector adjust; //調整値
		//三角コライダと球コライダの衝突判定
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//衝突しない位置まで戻す
			mPosition = mPosition + adjust;
		}
		break;
	}
}

void CEnemy2::TaskCollision()
{
	mCollider.ChangePriority();
//	mCollider2.ChangePriority();
//	mCollider3.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
//	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
//	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);
}
