#include "CShootBoss.h"
#include "CCollision.h"

#define VELOCITY -5
#define VELOCITYX 3

CShootBoss::CShootBoss()
	:mXdir(0.0f)
{
	LoadTexture("ShootBoss.tga");
	mPriority = 2;
	mTag = ESHOOTBOSS;
}

void CShootBoss::Update() {
	mY += VELOCITY;
	mX += mXdir * VELOCITYX;
	if (mY < -300 - mH) {
		Disable();
	}
	if (mX < -400 - mW || 400 + mW < mX) {
		Disable();
	}
}

void CShootBoss::Collision(CTask& r) {
	CCharacter& c = (CCharacter&)r;
	if (c.mTag == EPLAYER) {
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY - mH, 128, 128);
//			mEffect.SetXYWH(mX, mY - mH, 128, 128);
//			mEffect.mIndex = 0;
//			mEffect.Enable();
			Disable();
		}
	}
	if (c.mTag == ESHOOTPLAYER) {
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY - mH, 128, 128);
//			mEffect.SetXYWH(mX, mY - mH, 128, 128);
//			mEffect.mIndex = 0;
//			mEffect.Enable();
			Disable();
		}
	}
}
