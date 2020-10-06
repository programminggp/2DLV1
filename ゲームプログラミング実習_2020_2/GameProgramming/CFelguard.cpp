#include "CFelguard.h"

CModelX *CFelguard::spModel = 0;
int CFelguard::sCount = 0;

CFelguard::CFelguard()
{
	if (!sCount) {
		spModel = new CModelX();
		spModel->Load("felguard\\felguard-X.X");
		spModel->SeparateAnimationSet(0, 0, 700, "ALL");
	}
	sCount++;
	Init(spModel);
	ChangeAnimation(1, true, 700);
}

void CFelguard::Set(const CVector &pos, const CVector &rot, const CVector &scale)
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
}

CFelguard::~CFelguard()
{
	sCount--;
	if (!sCount)
	{
		delete spModel;
		spModel = 0;
	}
}
