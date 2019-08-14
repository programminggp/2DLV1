#include "CEnemy.h"
#include "CSceneGame.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"
#include "CPlayer.h"
#include <math.h>

#define VELOCITY 1

#define ENEMYSHOOTTIME	60

CEnemy::CEnemy()
	: mVelocityX(-1)
	, mVelocityY(0)
	, mFire(ENEMYSHOOTTIME)
	, mIsDead(false)
	, mFrame(0)
{
	mpTexture = &TexBomberman;
	mTag = EENEMY;
	CSceneGame::mCharacters.push_back(this);
}

CEnemy::CEnemy(float x, float y, float w, float h)
	: CEnemy()
{
	Set(x, y, w, h);
}


void CEnemy::Update() {
//	if (!mState) return;

	if (CPlayer::mpInstance->mX < mX) {
		mVelocityX = -1;
	}
	else if (CPlayer::mpInstance->mX > mX) {
		mVelocityX = 1;
	}
	if (CPlayer::mpInstance->mY < mY) {
		mVelocityY = -1;
	}
	else if (CPlayer::mpInstance->mY > mY) {
		mVelocityY = 1;
	}

	mX += mVelocityX * VELOCITY;
	mY += mVelocityY * VELOCITY;

	mFrame++;
}

void CEnemy::Render() {
	if (!mState) return;
	if (mVelocityX < 0) {
		CRectangle::Render(mX, mY, mW, mH, mpTexture, 0.0f, 16.0f, 256.0f, 241.0f);
	}
	else {
		CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 3, 16 * 4, 256.0f, 241.0f);
	}
}

void CEnemy::Collision(CCharacter* mc, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	float dx = 0.0f, dy = 0.0f;
	if (CCollision::Collision(mc, yc, &dx, &dy)) {
		switch (yc->mTag) {
		case EENEMY:
			mX += dx;
			mY += dy;
			break;
		case EBLOCK:
			mX += dx;
			mY += dy;
			mVelocityX = -mVelocityX;
			break;
		case EEXPLOSION:
			break;
		}
	}
}
