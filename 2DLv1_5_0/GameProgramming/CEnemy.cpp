#include "CEnemy.h"
#include "CSceneGame.h"
#include "CCollision.h"
#include "CRectangle.h"
#include "CPlayer.h"
#include "Define.h"

CEnemy::CEnemy()
: mFx(-1)
, mFy(0)
, mIsAlive(true)
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
	if (mIsAlive) {
		if (CPlayer::mpInstance->mTag == EPLAYER) {
			if (CPlayer::mpInstance->mX < mX) {
				mFx = -1;
			}
			else if (CPlayer::mpInstance->mX > mX) {
				mFx = 1;
			}
			if (CPlayer::mpInstance->mY < mY) {
				mFy = -1;
			}
			else if (CPlayer::mpInstance->mY > mY) {
				mFy = 1;
			}
		}
		mX += mFx * VELOCITY_E;
		mY += mFy * VELOCITY_E;
	}
	else {
		if (mFrame > 60) {
			mState = EDELETE;
		}
	}
	mFrame++;
}

void CEnemy::Render() {
	if (!mState) return;
	if (mIsAlive) {
		if (mFx < 0) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 0.0f, 16.0f, 256.0f, 241.0f);
		}
		else {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 3, 16 * 4, 256.0f, 241.0f);
		}
	}
	else {
		if (mFrame / 10 == 0) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 6, 16 * 7, 256.0f, 241.0f);
		}
		else if (mFrame / 10 == 1) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 7, 16 * 8, 256.0f, 241.0f);
		}
		else if (mFrame / 10 == 2) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 8, 16 * 9, 256.0f, 241.0f);
		}
		else if (mFrame / 10 == 3) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 9, 16 * 10, 255.0f, 241.0f);
		}
		else if (mFrame / 10 == 4) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 10, 16 * 11, 255.0f, 241.0f);
		}
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
			mFx = -mFx;
			break;
		//8Å@îöî≠è’ìÀ
		case EEXPLOSION:
			mIsAlive = false;
			mTag = EBACKGROUND;
			mFrame = 0;
			break;
		}
	}
}
