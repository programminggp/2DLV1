#include "CMap5.h"
#include "CRes.h"

#define OBJ "sea OBJ.obj"
#define MTL "sea MTL.mtl"

#define CAMERA_POSITION CVector(1.0f, 1.0f, 5.0f)
#define CAMERA_DISTANCE 7.0f

CMap5::CMap5()
	: mCameraControl(CAMERA_POSITION, CVector(), CAMERA_DISTANCE)
	, mPlayer(CVector(-0.0f, 18.0f, 5.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f))

{
	mpModel = &mModel;
	mModel.Load(OBJ, MTL);

//	mPosition = CVector(50.0f, 1.0f, 50.0f);
	mPosition = CVector(0.0f, 0.0f, 0.0f);
	mScale = CVector(40.0f, 40.0f, 40.0f);
	CTransform::Update();
	//メッシュでコライダを生成
//	mColMesh.Set(nullptr, &mMatrix, mpModel, CCollider::EGROUND);

	//キャラクターにモデルを設定
	CRes::sModelX.Load(MODEL_FILE);
	mPlayer.Init(&CRes::sModelX);
}
