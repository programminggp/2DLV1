#include "CAirBase.h"

//エフェクトクラスのインクルード
#include "CEffect.h"
//スマートポインタの外部参照
extern std::shared_ptr<CTexture> TextureExp;


//コンストラクタ
//CAirBase(モデル, 位置, 回転, 拡縮)
CAirBase::CAirBase(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(350.0f, 1.0f, -1800.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 5.0f)
{
	mCollider.mTag = CCollider::EBODY;
	mTag = EAIRBASE;
	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
}

//衝突処理
void CAirBase::Collision(CCollider *m, CCollider *y) {
	//共に球コライダの時
	if (m->mType == CCollider::ESPHERE
		&& y->mType == CCollider::ESPHERE) {
		if (y->mTag == CCollider::EBODY) {
			if (CCollider::Collision(m, y)) {
				//エフェクト生成
//				new CEffect(mPosition, 1.0f, 1.0f, TextureExp, 4, 4, 1);
				new CEffect(y->mPosition * y->mMatrix * y->mpParent->mMatrix, 5.0f, 5.0f, TextureExp, 4, 4, 1);
			}
		}
	}
}
