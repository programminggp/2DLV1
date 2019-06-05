#include "CBoss.h"
#include "CPlayer.h"
#include "CCollision.h"
#include "CUI.h"

#define VELOCITY 2

CTexture CBoss::mTexture;

CBoss::CBoss()
	: mVelocity(VELOCITY)
	, mHit(0)
{
	if (mTexture.mId == 0) {
		mTexture.Load("Boss.tga");
	}
	mTag = EBOSS;
}

CBoss::CBoss(float x, float y, float w, float h)
	: CBoss()
{
	Set(x, y, w, h);
}

void CBoss::Update() {
	mX += mVelocity;
	if (mX > 400 - mW || mX < -400 + mW) {
		mVelocity *= -1;
	}
	//if (mShootLeft.mStatus != EENABLED) {
	//	mShootLeft.SetXYWH(mX - mW / 2, mY - mH / 2, 34, 140);
	//	if (CPlayer::mpInstance->mX < mX - mW) {
	//		mShootLeft.mXdir = -1;
	//	}
	//	else if (CPlayer::mpInstance->mX > mX + mW) {
	//		mShootLeft.mXdir = 1;
	//	}
	//	else {
	//		mShootLeft.mXdir = 0;
	//	}
	//	mShootLeft.Enable();
	//}
	//if (mShootRight.mStatus != EENABLED) {
	//	mShootRight.SetXYWH(mX + mW / 2, mY - mH / 2, 34, 140);
	//	if (CPlayer::mpInstance->mX < mX - mW) {
	//		mShootRight.mXdir = -1;
	//	}
	//	else if (CPlayer::mpInstance->mX > mX + mW) {
	//		mShootRight.mXdir = 1;
	//	}
	//	else {
	//		mShootRight.mXdir = 0;
	//	}
	//	mShootRight.Enable();
	//}
}

void CBoss::Render() {
	CRectangle::Render(&mTexture, 0.0f, 159.0f, 240.0f, 0.0f);
	char buf[10];
	sprintf(buf, "%d", mHit);
//	mFont.Render(buf, mX - mW, mY + mH - 32, 24, 32);
}

void CBoss::Collision(CCharacter* my, CCharacter* you) {
	CCharacter& c = (CCharacter&)*you;
	if (c.mTag == ESHOOTPLAYER) {
		if (CCollision::Collision(*this, c)) {
			new CEffect(mX, mY, 128, 128);
			mHit++;
			CUI::mEnemyHit++;
		}
	}
}
