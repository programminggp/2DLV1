#include "CPlayer.h"
#include "CKey.h"

void CPlayer::Update() {
	if (CKey::Push('I')) {
		mPosition = mPosition + CVector(0.0f, 0.0f, 0.2f) * mMatrixRotation;
	}
	if (CKey::Push('A')) {
		mRotation.mY++;
//		mRotation.mZ--;
	}
	if (CKey::Push('D')) {
		mRotation.mY--;
//		mRotation.mZ++;
	}
	if (CKey::Push('W')) {
		mRotation.mX++;
	}
	if (CKey::Push('S')) {
		mRotation.mX--;
	}
	CCharacter::Update();
}
