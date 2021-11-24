#include "CGoblin.h"

CModelX CGoblin::mModel;

#define MODEL "goblin\\goblin-sapper-animated-X.X"

CGoblin::CGoblin()
	:mColHit(this,nullptr,CVector(0.0f, 0.0f, 0.0f), 0.8f)
{
	if (mModel.mFrame.size() == 0)
	{
		mModel.Load(MODEL);
		mModel.SeparateAnimationSet(0, 0, 680, "ALL");
		//mModel.SeparateAnimationSet(1, 0, 100, "IDLE");
		//mModel.SeparateAnimationSet(1, 150, 200, "ATTACK1");
		//mModel.SeparateAnimationSet(1, 200, 260, "ATTACK_IDLE");
		//mModel.SeparateAnimationSet(1, 260, 350, "ATTACK3");
		//mModel.SeparateAnimationSet(1, 380, 420, "WALK");
		//mModel.SeparateAnimationSet(1, 425, 460, "RUN");
		//mModel.SeparateAnimationSet(1, 470, 510, "DEATH1");
		//mModel.SeparateAnimationSet(1, 520, 700, "DEATH2");
	}
	mPosition = CVector(-5.0f, 0.0f, 1.0f);
	mScale = CVector(1.1f, 1.1f, 1.1f);
	Init(&mModel);
	ChangeAnimation(1, true, 680);
	//çáê¨çsóÒÇÃê›íË
	mColHit.mpMatrix = &mpCombinedMatrix[4];
}

void CGoblin::Update()
{
	CXCharacter::Update();
}
