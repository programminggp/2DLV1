#include "CEnemy.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"

#define VELOCITY 2

CEnemy::CEnemy()
	: mVelocity(VELOCITY)
{
//	LoadTexture("Enemy.tga");
	mPriority = 1;
	mTag = EENEMY;
	Enable();
}

void CEnemy::Update() {
	mY -= mVelocity;
	if (mY < -400) {
		Delete();
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

void CEnemy::Render() {
	CRectangle::Render();
}

void CEnemy::Collision(CTask& r) {
	CCharacter& c = (CCharacter&)r;
	if (c.mTag == ESHOOTPLAYER) {
		if (CCollision::Collision(*this, c)) {
			new CEffect(mX, mY, 128, 128);
			//CEffect *effect = new CEffect();
			//effect->SetXYWH(mX, mY, 128, 128);
			//effect->mIndex = 0;
			//effect->Enable();
			CUI::mEnemyHit++;
			Delete();
		}
	}
}
