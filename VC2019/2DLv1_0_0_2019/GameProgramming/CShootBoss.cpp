#include "CShootBoss.h"
#include "CCollision.h"
#include "CRectangle.h"

#define VELOCITY -5
#define VELOCITYX 3

CTexture CShootBoss::mTexture;


CShootBoss::CShootBoss()
	:mXdir(0.0f)
{
	if (mTexture.mId == 0) {
		mTexture.Load("ShootBoss.tga");
	}
	mTag = ESHOOTBOSS;
}

void CShootBoss::Update() {
	mY += VELOCITY;
	mX += mXdir * VELOCITYX;
	if (mY < -300 - mH) {
		mState = EDISABLED;
	}
	if (mX < -400 - mW || 400 + mW < mX) {
		mState = EDISABLED;
	}
}

void CShootBoss::Collision(CCharacter* mc, CCharacter* yc) {
	if (yc->mTag == EPLAYER) {
		if (CCollision::Collision(this, yc)) {
			new CEffect(mX, mY - mH, 128, 128);
			mState = EDISABLED;
		}
	}
	else if (yc->mTag == EPLAYERSHOT) {
		if (CCollision::Collision(this, yc)) {
			new CEffect(mX, mY - mH, 128, 128);
			mState = EDISABLED;
		}
	}
}

void CShootBoss::Render() {
	CRectangle::Render(mX, mY, mW, mH, &mTexture, 0.0f, 34.0f, 140.0f, 0.0f);
}