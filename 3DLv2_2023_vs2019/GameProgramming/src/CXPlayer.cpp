#include "CXPlayer.h"

void CXPlayer::Update()
{
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
	CXCharacter::Update();
}