#include "CMap2.h"
#include "CRes.h"

#define OBJ "UnderGround\\passage2.obj"
#define MTL "UnderGround\\passage2.mtl"

CMap2::CMap2()
	:mPlayer(CVector(-70.0f, 18.0f, 525.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f))
{
	mpModel = &mModel;
	mModel.Load(OBJ, MTL);
//	mPosition = CVector(50.0f, 10.0f, 50.0f);
	mPosition = CVector(0.0f, 0.0f, 0.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();
	//メッシュでコライダを生成
	mColMesh.Set(nullptr, &mMatrix, mpModel, CCollider::EGROUND);

	//キャラクターにモデルを設定
	CRes::sModelX.Load(MODEL_FILE);
	mPlayer.Init(&CRes::sModelX);
}
