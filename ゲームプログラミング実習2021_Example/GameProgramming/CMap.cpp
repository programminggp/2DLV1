#include "CMap.h"

CMap::CMap()
{
	mpModel = &mModel;
	mModel.Load("sky.obj", "sky.mtl");
	mPosition = CVector(0.0f, 1.0f, 0.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();
}
