#include "CEnemy.h"

//コンストラクタ
//CEnemy(モデル, 位置, 回転, 拡縮)
CEnemy::CEnemy(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 0.8f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model;	//モデルの設定
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
}
//更新処理
void CEnemy::Update() {
	//行列を更新
	CCharacter::Update();
	//位置を移動
	mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	//回転させる
	mRotation.mY += 0.5f;
}

void CEnemy::Collision(CCollider *m, CCollider *y) {
	if (CCollider::Collision(m, y)) {
		mEnabled = false;
		printf("CEnemy Hit!\n");
	}
}