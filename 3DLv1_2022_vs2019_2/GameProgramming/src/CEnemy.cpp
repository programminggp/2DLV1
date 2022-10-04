#include "CEnemy.h"

//移動速度
#define VELOCITY CVector(0.0f, 0.0f, 0.09f)

//コンストラクタ
//CEnemy(モデル, 位置, 回転, 拡縮)
CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
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
	CTransform::Update();
	//位置を移動
	mPosition = mPosition + VELOCITY * mMatrixRotate;
}
