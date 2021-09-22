#include "CFelguard.h"

CModelX CFelguard::mModel;

#define MODEL "felguard\\felguard-X.X"

CFelguard::CFelguard()
{
	if (mModel.mFrame.size() == 0)
	{
		mModel.Load(MODEL);
		mModel.SeparateAnimationSet(0, 0, 701, "ALL");
	}
	mPosition = CVector(-5.0f, 0.0f, 1.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	Init(&mModel);
	ChangeAnimation(1, true, 700);
}

void CFelguard::Update()
{
	CXCharacter::Update();
}
