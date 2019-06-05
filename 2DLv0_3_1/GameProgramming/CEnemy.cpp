#include "CEnemy.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"
#include "CShootEnemy.h"
#include "CPlayer.h"
#include <math.h>
#include "CTextureManager.h"

#define VELOCITY 4

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
	if (!mEnabled) return;

	if (mFire > 0) {
		mFire--;
	}
	if (mFire == 0) {
		if (abs(CPlayer::mpInstance->mX - mX) < 60) {
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
	mX += mVelocity;
	if (mY < -300) {
		mY = 250;
	}
}

void CEnemy::Render() {
	if (!mEnabled) return;
	CRectangle::Render(mpTexture, 0.0f, 48.0f, 72.0f, 0.0f);
}

void CEnemy::Collision(CCharacter* mc, CCharacter* yc) {
	if (!mEnabled) return;
	if (yc->mTag == ESHOOTPLAYER) {
		if (CCollision::Collision(*this, *yc)) {
			new CEffect(mX, mY, 128, 128);
			CUI::mEnemyHit++;
			mEnabled = false;
		}
	}
}
