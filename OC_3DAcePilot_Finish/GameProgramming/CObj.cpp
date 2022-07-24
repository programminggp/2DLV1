#include "CObj.h"
#include "CCollisionManager.h"

//コンストラクタ
//model：モデルのポインタ　posision：位置　rotation：回転　scale：拡縮
CObj::CObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
: mpCollider(0)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	//モデルの三角形の数分、コライダの配列を作成します
	mpCollider = new CCollider[model->mTriangles.size()];
	for (int i = 0; i < model->mTriangles.size(); i++) {
		//コライダを三角形コライダで設定していきます
		mpCollider[i].SetTriangle(this,
			model->mTriangles[i].mV[0],
			model->mTriangles[i].mV[1],
			model->mTriangles[i].mV[2]);
		CollisionManager.ChangePriority(&mpCollider[i], -1);
	}
}
//デストラクタ
CObj::~CObj() {
	//コライダがあれば削除
	if (mpCollider) {
		//delete[]　配列を削除
		delete[] mpCollider;
	}
}
