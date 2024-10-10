#include "CMap.h"

#define CMAP_GROUND "res\\sky.obj", "res\\sky.mtl"

#define POSITION 0.0f,0.0f,0.0f
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
}
