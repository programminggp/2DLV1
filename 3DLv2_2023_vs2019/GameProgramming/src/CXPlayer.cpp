#include "CXPlayer.h"

void CXPlayer::Update()
{
	if (mInput.Key('W')) {
		ChangeAnimation(1, true, 60);
		mPosition = mPosition + CVector(0.0f, 0.0f, 0.1f);
	}
	else
	{
		ChangeAnimation(0, true, 60);
	}
	CXCharacter::Update();
}