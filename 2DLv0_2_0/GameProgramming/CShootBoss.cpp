#include "CShootBoss.h"
#include "CCollision.h"

#define VELOCITY -5
#define VELOCITYX 3

CTexture CShootBoss::mTexture;


CShootBoss::CShootBoss()
	:mXdir(0.0f)
{
	if (mTexture.mId == 0) {
		mTexture.Load("ShootBoss.tga");
	}
//	mPriority = 2;
	mTag = ESHOOTBOSS;
}

void CShootBoss::Update() {
	mY += VELOCITY;
	mX += mXdir * VELOCITYX;
	if (mY < -300 - mH) {
		mState = EDELETE;
//		Disable();
	}
	if (mX < -400 - mW || 400 + mW < mX) {
		mState = EDELETE;
//		Disable();
	}
}

void CShootBoss::Collision(CCharacter* my, CCharacter* yr) {
	CCharacter& c = (CCharacter&)*yr;
	if (c.mTag == EPLAYER) {
		if (CCollision::Collision(*this, c)) {
			new CEffect(mX, mY - mH, 128, 128);
			mState = EDELETE;
			//Disable();
		}
	}
	if (c.mTag == ESHOOTPLAYER) {
		if (CCollision::Collision(*this, c)) {
			new CEffect(mX, mY - mH, 128, 128);
			mState = EDELETE;
			//Disable();
		}
	}
}

void CShootBoss::Render() {
	CRectangle::Render(&mTexture, 0.0f, 34.0f, 140.0f, 0.0f);
}