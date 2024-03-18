#include "CXPlayer.h"

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.Matrix(&mpCombinedMatrix[8]);
	//��
	mColSphereHead.Matrix(&mpCombinedMatrix[11]);
	//��
	mColSphereSword.Matrix(&mpCombinedMatrix[21]);
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
