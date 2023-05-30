#include "CXPlayer.h"

void CXPlayer::Update()
{
	switch (AnimationIndex())
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
		if (mInput.Key('A')) {
			mRotation.Y(mRotation.Y() + 2.0f);
		}
		if (mInput.Key('D')) {
			mRotation.Y(mRotation.Y() - 2.0f);
		}
		if (mInput.Key('W')) {
			ChangeAnimation(1, true, 60);
			mPosition = mPosition + MatrixRotate().VectorZ() * 0.1f;
		}
		else
		{
			ChangeAnimation(0, true, 60);
		}
		if (mInput.Key(' '))
		{
			ChangeAnimation(3, false, 30);
		}
	}
	CXCharacter::Update();
}