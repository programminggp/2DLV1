#include "CShootPlayer.h"
#include "CCollision.h"

#define VELOCITY 10

CShootPlayer::CShootPlayer()
{
	LoadTexture("ShootPlayer.tga");
	mPriority = 2;
	mTag = ESHOOTPLAYER;
}

void CShootPlayer::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		Disable();
	}
}

void CShootPlayer::Collision(CTask& r) {
	CCharacter& c = (CCharacter&)r;
	if (c.mTag == EBOSS) {
		if (CCollision::Collision(*this, c)) {
			mEffect.SetXYWH(mX, mY + mH, 128, 128);
			mEffect.mIndex = 0;
			mEffect.Enable();
			Disable();
		}
	}
	if (c.mTag == ESHOOTBOSS) {
		if (CCollision::Collision(*this, c)) {
			mEffect.SetXYWH(mX, mY + mH, 128, 128);
			mEffect.mIndex = 0;
			mEffect.Enable();
			Disable();
		}
	}
}
