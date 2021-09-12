#include "CFelguard.h"

CModelX CFelguard::sModel;

CFelguard::CFelguard()
{
	if (sModel.mFrame.size() == 0) {
		sModel.Load("felguard\\felguard-X.X");
		sModel.SeparateAnimationSet(0, 0, 700, "ALL");
	}
	Init(&sModel);
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
}
