#include "CFreeMonster.h"

CModelX CFreeMonster::sModel;

CFreeMonster::CFreeMonster()
{
	if (sModel.mFrame.size() == 0) {
		sModel.Load("freemonster\\monster-animated-character-X.X");
	}
	Init(&sModel);
}

void CFreeMonster::Set(const CVector &pos, const CVector &rot, const CVector &scale)
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
}

CFreeMonster::~CFreeMonster()
{
	//if (!sCount)
	//{
	//	delete spModel;
	//	spModel = 0;
	//}
}
