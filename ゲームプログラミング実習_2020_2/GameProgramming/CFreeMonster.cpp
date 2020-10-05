#include "CFreeMonster.h"

CModelX *CFreeMonster::spModel = 0;
int CFreeMonster::sCount = 0;

CFreeMonster::CFreeMonster()
{
	if (!sCount) {
		spModel = new CModelX();
		spModel->Load("freemonster\\monster-animated-character-X.X");
	}
	sCount++;
	Init(spModel);
}

void CFreeMonster::Set(const CVector &pos, const CVector &rot, const CVector &scale)
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
}

CFreeMonster::~CFreeMonster()
{
	sCount--;
	if (!sCount)
	{
		delete spModel;
		spModel = 0;
	}
}
