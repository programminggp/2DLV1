#include "CMap.h"

//#define CMAP_GROUND "res\\sky.obj", "res\\sky.mtl"
#define CMAP_GROUND "res\\UnderGround\\passage2.obj","res\\UnderGround\\passage2.mtl"

#define POSITION 45.0f,12.0f,0.0f
#define ROTATION 0.0f,0.0f,0.0f
#define SCALE 1.0f,1.0f,1.0f

CModel CMap::mModel;
bool CMap::mLoad = true;


CMap::CMap()
{
	if (mLoad)
	{
		mLoad = false;
		mModel.Load(CMAP_GROUND);
	}
	Model(&mModel);
	Position(CVector(POSITION));
	Rotation(CVector(ROTATION));
	Scale(CVector(SCALE));
	CTransform::Update();
	mColMesh.Set(this, &mMatrix, &mModel);
}
