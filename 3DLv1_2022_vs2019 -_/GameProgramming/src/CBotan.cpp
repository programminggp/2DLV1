#include "CBotan.h"
#include "CApplication.h"

void CBotan::Collision()
{
	//コライダの優先度変更
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mCollider1, 30);
	CCollisionManager::Instance()->Collision(&mCollider2, 30);
	CCollisionManager::Instance()->Collision(&mCollider3, 30);
}

//衝突処理
//Collision(コライダ１、 コライダ２)
void CBotan::Collision(CCollider* m, CCollider* o)
{
	//相手のコライダタイプの作成
	switch (o->Type())
	{
	case CCollider::ESPHERE: //球コライダの時
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, o)) {
			//衝突している時は無効にする
			//mEnabled = false;
		}
		break;
	case CCollider::ETRIANGLE: //三角コライダの時
		CVector adjust; //調整値
		//三角コライダと球コライダの衝突処理
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{   //衝突しない位置まで戻す
			mPosition = mPosition + adjust;
		}
		break;
	}
}

//コンストラクタ
//CBotan(モデル、位置、回転、拡縮)
CBotan::CBotan(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -20.0f), 0.8f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定
}

//更新処理
void CBotan::Update() {
	//行列を更新
	CTransform::Update();
}