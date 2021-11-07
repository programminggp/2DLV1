#include "CMap4.h"
#include "CRes.h"

#define OBJ "crypt-location\\12.obj"
#define MTL "crypt-location\\12.mtl"

#define CAMERA_POSITION CVector(1.0f, 1.0f, 5.0f)
#define CAMERA_DISTANCE 7.0f

CMap4::CMap4()
	: mCameraControl(CAMERA_POSITION, CVector(), CAMERA_DISTANCE)
	, mPlayer(CVector(-0.0f, 18.0f, 5.0f), CVector(0.0f, 180.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f))

{
	mpModel = &mModel;
	mModel.Load(OBJ, MTL);

//	mPosition = CVector(50.0f, 1.0f, 50.0f);
	mPosition = CVector(0.0f, 0.0f, 0.0f);
	mScale = CVector(2.0f, 2.0f, 2.0f);
	CTransform::Update();
	//メッシュでコライダを生成
	mColMesh.Set(nullptr, &mMatrix, mpModel, CCollider::EGROUND);

	//キャラクターにモデルを設定
	CRes::sModelX.Load(MODEL_FILE);
	mPlayer.Init(&CRes::sModelX);
}
