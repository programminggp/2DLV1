#include "CXPlayer.h"

#include "CKey.h"


CXPlayer::CXPlayer() {
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

void CXPlayer::Update() {

	if (CKey::Push('A')) {
		mRotation.mY += 2;
	}
	if (CKey::Push('D')) {
		mRotation.mY -= 2;
	}

	if (CKey::Push('W')) {
		ChangeAnimation(1, true, 60);
		mPosition = mPosition + CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
//		mPosition.mZ += 0.1f;
	}
	else {
		ChangeAnimation(0, true, 60);
	}

	CXCharacter::Update();
}