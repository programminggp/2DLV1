#include "CShootPlayer2.h"
#include "CCollision.h"

#define VELOCITY 10

CShootPlayer2::CShootPlayer2()
{
	LoadTexture("ShootPlayer.tga");
	mPriority = 2;
	mTag = ESHOOTPLAYER;
	Enable();
}

void CShootPlayer2::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		Delete();
	}
}

void CShootPlayer2::Collision(CTask& r) {
	CCharacter& c = (CCharacter&)r;
	if (c.mTag == EBOSS) {
		if (CCollision::Collision(*this, c)) {
			//mEffect.SetXYWH(mX, mY + mH, 128, 128);
			//mEffect.mIndex = 0;
			//mEffect.Enable();
			//Disable();
			Delete();
		}
	}
	if (c.mTag == ESHOOTBOSS) {
		if (CCollision::Collision(*this, c)) {
			//mEffect.SetXYWH(mX, mY + mH, 128, 128);
			//mEffect.mIndex = 0;
			//mEffect.Enable();
			//Disable();
			Delete();
		}
	}
}
