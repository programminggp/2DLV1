#include "CFelguard.h"

CModelX CFelguard::mModel;

#define MODEL "res\\felguard\\felguard-X.X"

CFelguard::CFelguard()
	:mColHit(this,nullptr,CVector(0.0f, 0.0f, 0.0f), 0.8f)
{
	if (!mModel.IsLoaded())
	{
		mModel.Load(MODEL);
		mModel.SeparateAnimationSet(0, 0, 701, "ALL");
		mModel.SeparateAnimationSet(1, 0, 100, "IDLE");
		mModel.SeparateAnimationSet(1, 150, 200, "ATTACK1");
		mModel.SeparateAnimationSet(1, 200, 260, "ATTACK_IDLE");
		mModel.SeparateAnimationSet(1, 260, 350, "ATTACK3");
		mModel.SeparateAnimationSet(1, 380, 420, "WALK");
		mModel.SeparateAnimationSet(1, 425, 460, "RUN");
		mModel.SeparateAnimationSet(1, 470, 510, "DEATH1");
		mModel.SeparateAnimationSet(1, 520, 700, "DEATH2");
	}
	mPosition = CVector(-5.0f, 0.0f, -5.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	Init(&mModel);
	ChangeAnimation(1, true, 700);
	//�����s��̐ݒ�
	mColHit.Matrix(&mpCombinedMatrix[4]);
}

void CFelguard::Update()
{
	CXCharacter::Update();
}