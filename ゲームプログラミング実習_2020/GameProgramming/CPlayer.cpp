#include "CPlayer.h"
#include "CKey.h"

void CPlayer::Update() {
	if (CKey::Push('A')) {
		mRotation.mY++;
	}
	if (CKey::Push('D')) {
		mRotation.mY--;
	}
	//5
	if (CKey::Push('W')) {
		mPosition = CVector(0.0f, 0.0f, 0.5f) * mMatrix;
	}
	CCharacter::Update();
}
