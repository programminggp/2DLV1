#include "CXPlayer.h"

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//çáê¨çsóÒÇÃê›íË
	mColSphereBody.Matrix(&mpCombinedMatrix[9]);
	//ì™
	mColSphereHead.Matrix(&mpCombinedMatrix[12]);
	//åï
	mColSphereSword.Matrix(&mpCombinedMatrix[22]);
}

void CXPlayer::Update()
{
	switch (mAnimationIndex)
	{
	case 3:
		if (IsAnimationFinished())
		{
			ChangeAnimation(4, false, 30);
		}
		break;
	case 4:
		if (IsAnimationFinished())
		{
			ChangeAnimation(0, true, 60);
		}
		break;
	default:
		if (mInput.Key('A'))
		{
			mRotation.Y(mRotation.Y() + 2.0f);
		}
		if (mInput.Key('D'))
		{
			mRotation.Y(mRotation.Y() - 2.0f);
		}
		if (mInput.Key('W'))
		{
			ChangeAnimation(1, true, 60);
			Position(Position() + mMatrixRotate.VectorZ() * 0.1);
		}
		else
		{
			ChangeAnimation(0, true, 60);
		}
		if (mInput.Key(VK_SPACE))
		{
			ChangeAnimation(3, false, 30);
		}
	}
	CXCharacter::Update();
}
