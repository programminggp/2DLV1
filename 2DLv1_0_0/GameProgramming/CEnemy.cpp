#include "CEnemy.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"
#include "CShootEnemy.h"
#include "CPlayer.h"
#include <math.h>
#include "CSceneGame.h"

#define VELOCITY 5

#define ENEMYSHOOTTIME	60

CEnemy::CEnemy()
	: mVelocity(VELOCITY)
	, mFire(ENEMYSHOOTTIME)
{
	mTag = EENEMY;
}

CEnemy::CEnemy(float x, float y, float w, float h)
	: CEnemy()
{
	Set(x, y, w, h);
}

void CEnemy::Update() {
	if (mState == EDISABLED) mState = EDISABLED;
	if (!mState) return;

	//if (mFire > 0) {
	//	mFire--;
	//}
	//if (mFire == 0) {
	//	if (abs(CPlayer::mpInstance->mX - mX) < 40) {
	//		new CShootEnemy(mX, mY, 12, 32);
	//		mFire = ENEMYSHOOTTIME;
	//	}
	//}

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
	if (!mState) return;
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 0.0f, 48.0f, 72.0f, 0.0f);
}

void CEnemy::Collision(CCharacter* mc, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	if (CCollision::Collision(*this, *yc)) {
		if (yc->mTag == ESHOOTPLAYER) {
			//new CEffect(mX, mY, 64, 64);
			//CUI::mEnemyHit++;
			mState = EDISABLED;
		}
	}
}
