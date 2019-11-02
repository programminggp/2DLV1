#include "CEnemy.h"

//コンストラクタ
//CEnemy(モデル, 位置, 回転, 拡縮)
CEnemy::CEnemy(CModel *model, CVector position, CVector rotation, CVector scale) {
	//モデル、位置、回転、拡縮を設定する
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
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
