#include "CWarrok.h"

CModelX CWarrok::mModel;

//#define MODEL "warrok\\idle.fbx.x"
//#define MODEL "mutant\\mutant.x"
//#define ANI_ATTACK "warrok\\Standing Torch Melee Attack 01.fbx.x"
#define MODEL "mutant\\mutant.x"
#define ANI_ATTACK "mutant\\mutant@WalkingBackwards.fbx.x"

CWarrok::CWarrok()
	:mColHit(this,nullptr,CVector(0.0f, 0.0f, 0.0f), 0.8f)
{
	if (mModel.mFrame.size() == 0)
	{
		mModel.Load(MODEL);
		mModel.AddAnimationSet(ANI_ATTACK);
		//mModel.SeparateAnimationSet(0, 0, 701, "ALL");
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
	mRotation.mY = 0.0f;
	mScale = CVector(3.0f, 3.0f, 3.0f);
	Init(&mModel);
	ChangeAnimation(0, true, 250);
	//çáê¨çsóÒÇÃê›íË
	mColHit.mpMatrix = &mpCombinedMatrix[4];
}

void CWarrok::Update()
{
	CXCharacter::Update();
}
