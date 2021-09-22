#include "CMap.h"

#define OBJ "UnderGround\\passage2.obj"
#define MTL "UnderGround\\passage2.mtl"

CMap::CMap()
{
	mpModel = &mModel;
	mModel.Load(OBJ, MTL);
	mPosition = CVector(50.0f, 10.0f, 50.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();
}
