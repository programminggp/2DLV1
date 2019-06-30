#include "CEnemy.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"
#include "CEnemyShot.h"
#include "CPlayer.h"
#include <math.h>
#include "CSceneGame.h"

#define VELOCITY 5

#define ENEMYSHOOTTIME	60

CEnemy::CEnemy()
	: mVelocity(VELOCITY)
	, mShot(ENEMYSHOOTTIME)
{
	mTag = EENEMY;
}

CEnemy::CEnemy(float x, float y, float w, float h)
	: CEnemy()
{
	Set(x, y, w, h);
}

void CEnemy::Update() {
	mEffect.Update();
	if (mState == EDISABLED) mState = EDELETE;
	if (!mState) return;

	if (mShot > 0) {
		mShot--;
	}
	else {
//		if (abs(CPlayer::mpInstance->mX - mX) < 40) {
		for (int i = 0; i < 5; i++) {
			if (CEnemyShot::mShot[i].mState == EDELETE) {
				CEnemyShot::mShot[i].Set(mX, mY, 12, 32);
				CEnemyShot::mShot[i].mState = EENABLED;
				mShot = ENEMYSHOOTTIME;
				break;
			}
		}
	}

	mX += mVelocity;
	if (mX > 800) {
		mVelocity *= -1;
	}
	else if (mX < 0) {
		mVelocity *= -1;
	}
	mY -= VELOCITY / 2;
	if (mY < -72) {
		mY = 672;
	}
}

void CEnemy::Render() {
	if (mState) {
		CRectangle::Render(mX, mY, mW, mH, mpTexture, 0.0f, 48.0f, 72.0f, 0.0f);
	}
	mEffect.Render();
}

void CEnemy::Collision(CCharacter* mc, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	if (CCollision::Collision(this, yc)) {
		if (yc->mTag == EPLAYERSHOT) {
			mEffect.Set(mX, mY, 64, 64);
			mEffect.mState = EENABLED;
			//new CEffect(mX, mY, 64, 64);
			//CUI::mEnemyHit++;
			//mState = EDISABLED;
		}
	}
}
