#include "CBoss.h"
#include "CPlayer.h"
#include "CCollision.h"
#include "CUI.h"

#define VELOCITY 2

CBoss::CBoss()
	: mVelocity(VELOCITY)
	, mHit(0)
	, mFont("Font.tga", 1, 64, 16, 33)
{
	LoadTexture("Boss.tga");
	mPriority = 1;
	mTag = EBOSS;
	Enable();
}

void CBoss::Update() {
	mX += mVelocity;
	if (mX > 400 - mW || mX < -400 + mW) {
		mVelocity *= -1;
	}
	if (mShootLeft.mStatus != EENABLED) {
		mShootLeft.SetXYWH(mX - mW / 2, mY - mH / 2, 34, 140);
		if (CPlayer::mpInstance->mX < mX - mW) {
			mShootLeft.mXdir = -1;
		}
		else if (CPlayer::mpInstance->mX > mX + mW) {
			mShootLeft.mXdir = 1;
		}
		else {
			mShootLeft.mXdir = 0;
		}
		mShootLeft.Enable();
	}
	if (mShootRight.mStatus != EENABLED) {
		mShootRight.SetXYWH(mX + mW / 2, mY - mH / 2, 34, 140);
		if (CPlayer::mpInstance->mX < mX - mW) {
			mShootRight.mXdir = -1;
		}
		else if (CPlayer::mpInstance->mX > mX + mW) {
			mShootRight.mXdir = 1;
		}
		else {
			mShootRight.mXdir = 0;
		}
		mShootRight.Enable();
	}
}

void CBoss::Render() {
	CRectangle::Render();
	char buf[10];
	sprintf(buf, "%d", mHit);
	mFont.Render(buf, mX - mW, mY + mH - 32, 24, 32);
}

void CBoss::Collision(CTask& r) {
	CCharacter& c = (CCharacter&)r;
	if (c.mTag == ESHOOTPLAYER) {
		if (CCollision::Collision(*this, c)) {
			new CEffect(mX, mY, 128, 128);
			mHit++;
			CUI::mEnemyHit++;
		}
	}
}
