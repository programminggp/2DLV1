#include "CKnight.h"
#include "CKey.h"
#define _USE_MATH_DEFINES
#include "math.h"

CModelX CKnight::mModel;

#define MODEL "knight\\knight_low.X"

#define VELOCITY (0.1f)

CKnight::CKnight()
	:mColHit(this,nullptr, CVector(0.0f, 1.f, 0.0f), 1.5f)
{
	if (mModel.mFrame.size() == 0)
	{
		mModel.Load(MODEL);
		mModel.SeparateAnimationSet(0, 10, 80, "WALK");	//1
		mModel.SeparateAnimationSet(0, 90, 160, "WALKBACK");
		mModel.SeparateAnimationSet(0, 170, 220, "RUN");
		mModel.SeparateAnimationSet(0, 230, 300, "LEFT");
		mModel.SeparateAnimationSet(0, 300, 370, "RIGHT");	//5
		mModel.SeparateAnimationSet(0, 380, 430, "JUMP");
		mModel.SeparateAnimationSet(0, 440, 520, "ATTACK1");
		mModel.SeparateAnimationSet(0, 520, 615, "ATTACK2");
		mModel.SeparateAnimationSet(0, 615, 795, "ATTACK3");
		mModel.SeparateAnimationSet(0, 795, 850, "ATTACK4");	//10
		mModel.SeparateAnimationSet(0, 850, 970, "ATTACK5");
		mModel.SeparateAnimationSet(0, 970, 1040, "ATTACK6");
		mModel.SeparateAnimationSet(0, 1040, 1080, "HIT1");
		mModel.SeparateAnimationSet(0, 1080, 1120, "HIT2");
		mModel.SeparateAnimationSet(0, 1120, 1160, "HIT3");	//15
		mModel.SeparateAnimationSet(0, 1160, 1260, "DEATH1");
		mModel.SeparateAnimationSet(0, 1270, 1370, "DEATH2");
		mModel.SeparateAnimationSet(0, 1380, 1530, "IDLE1");
		mModel.SeparateAnimationSet(0, 1530, 1830, "IDLE2");
		mModel.SeparateAnimationSet(0, 1830, 1930, "EMOTION1");	//20
		mModel.SeparateAnimationSet(0, 1930, 2040, "EMOTION2");
	}
	mPosition = CVector(5.0f, 0.0f, 2.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	Init(&mModel);
	mModel.mFrame[0]->mTransformMatrix.RotateY(180.0f);
	ChangeAnimation(0, true, 2040);
	//çáê¨çsóÒÇÃê›íË
	mColHit.mpMatrix = &mpCombinedMatrix[1];
}

CKnight::CKnight(const CVector& pos, const CVector& rot, const CVector& scale)
	: CKnight()
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
}

void CKnight::Update()
{
	if (CKey::Push('J'))
	{
		mRotation.mY += 1;
	}
	if (CKey::Push('L'))
	{
		mRotation.mY -= 1;
	}
	if (CKey::Push('I'))
	{
		float radX = mRotation.mX / 180.0f * M_PI;
		float radY = mRotation.mY / 180.0f * M_PI;
		mPosition.mX += VELOCITY * cosf(radX) * sinf(radY);
		mPosition.mY += VELOCITY * sinf(radX);
		mPosition.mZ += VELOCITY * cosf(radX) * cosf(radY);
	}
	CXCharacter::Update();
}
