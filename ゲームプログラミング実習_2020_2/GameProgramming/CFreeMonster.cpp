#include "CFreeMonster.h"

CModelX *CFreeMonster::spModel = 0;
CFreeMonster::CFreeMonster()
{
	if (!spModel) {
		spModel = new CModelX();
		spModel->Load("freemonster\\monster-animated-character-X.X");
		Init(spModel);
	}
}

void CFreeMonster::Set(const CVector &pos, const CVector &rot, const CVector &scale)
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
}

CFreeMonster::~CFreeMonster()
{
	if (spModel)
	{
		delete spModel;
		spModel = 0;
	}
}
