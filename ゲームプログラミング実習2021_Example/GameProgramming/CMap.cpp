#include "CMap.h"

#define OBJ "sky.obj"
#define MTL "sky.mtl"

CMap::CMap()
{
	mpModel = &mModel;
	mModel.Load(OBJ, MTL);

	mPosition = CVector(50.0f, 1.0f, 50.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();
}
