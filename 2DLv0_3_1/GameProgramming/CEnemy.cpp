#include "CEnemy.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"
#include "CShootEnemy.h"
#include "CPlayer.h"
#include <math.h>
#include "CTextureManager.h"

#define VELOCITY 3

#define ENEMYSHOOTTIME	60

CEnemy::CEnemy()
	: mVelocity(VELOCITY)
	, mFire(ENEMYSHOOTTIME)
{
	mpTexture = &CTextureManager::mEnemy;
	mTag = EENEMY;
}

CEnemy::CEnemy(float x, float y, float w, float h)
	: CEnemy()
{
	Set(x, y, w, h);
}


void CEnemy::Update() {
	if (mState == ECOLLISION) mState = EDISABLED;
	if (!mState) return;

	if (mFire > 0) {
		mFire--;
	}
	if (mFire == 0) {
		if (abs(CPlayer::mpInstance->mX - mX) < 40) {
			new CShootEnemy(mX, mY, 24, 64);
			mFire = ENEMYSHOOTTIME;
		}
	}

	if (mX > 400) {
		mVelocity *= -1;
		mY -= mH * 2;
	}
	else if (mX < -400) {
		mVelocity *= -1;
		mY -= mH * 2;
	}
//	mX += mVelocity;
	mY -= mVelocity;
	if (mY < -300) {
		mY = 250;
	}
}

void CEnemy::Render() {
	if (!mState) return;
	CRectangle::Render(mpTexture, 0.0f, 48.0f, 72.0f, 0.0f);
}

void CEnemy::Collision(CCharacter* mc, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	if (CCollision::Collision(*this, *yc)) {
		if (yc->mTag == ESHOOTPLAYER) {
			new CEffect(mX, mY, 128, 128);
			CUI::mEnemyHit++;
			mState = ECOLLISION;
		}
	}
}
