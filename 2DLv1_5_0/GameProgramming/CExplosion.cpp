#include "CExplosion.h"
#include "CRectangle.h"
#include "CCollision.h"
#include "CSceneGame.h"

#define BOMBTIME 60 * 0.5f

CExplosion::CExplosion()
: mFrame(0), mU(0.0f), mV(0.0f)
{
	mpTexture = &TexBomberman;
	mTag = EEXPLOSION;
	CSceneGame::mCharacters.push_back(this);
}


CExplosion::CExplosion(float x, float y, float w, float h, int count)
: CExplosion()
{
	Set(x, y, w, h);
	mTagExp = ECENTER;
	mU = 16 * 2;
	mV = 16 * 6;
	mCount = count;
	if (count) {
		new CExplosion(x, y + CHIPSIZE * 2, w, h, count - 1, EUP);
		new CExplosion(x, y - CHIPSIZE * 2, w, h, count - 1, EDOWN);
		new CExplosion(x + CHIPSIZE * 2, y, w, h, count - 1, ERIGHT);
		new CExplosion(x - CHIPSIZE * 2, y, w, h, count - 1, ELEFT);
	}
}

CExplosion::CExplosion(float x, float y, float w, float h, int count, ETagExp tag)
: CExplosion()
{
	Set(x, y, w, h);
	mCount = count;
	mTagExp = tag;
	if (count) {
		switch (mTagExp) {
		case EUP:
			mU = 16 * 2;
			mV = 16 * 5;
			break;
		case EDOWN:
			mU = 16 * 2;
			mV = 16 * 7;
			break;
		case ERIGHT:
			mU = 16 * 3;
			mV = 16 * 6;
			break;
		case ELEFT:
			mU = 16 * 1;
			mV = 16 * 6;
			break;
		}
	}
	else {
		switch (mTagExp) {
		case EUP:
			mU = 16 * 2;
			mV = 16 * 4;
			break;
		case EDOWN:
			mU = 16 * 2;
			mV = 16 * 8;
			break;
		case ERIGHT:
			mU = 16 * 4;
			mV = 16 * 6;
			break;
		case ELEFT:
			mU = 16 * 0;
			mV = 16 * 6;
			break;
		}
	}
}

void CExplosion::Update() {
	if (mFrame == 2 && mCount > 0) {
		switch (mTagExp) {
		case EUP:
			new CExplosion(mX, mY + CHIPSIZE * 2, mW, mH, mCount - 1, EUP);
			break;
		case EDOWN:
			new CExplosion(mX, mY - CHIPSIZE * 2, mW, mH, mCount - 1, EDOWN);
			break;
		case ERIGHT:
			new CExplosion(mX + CHIPSIZE * 2, mY, mW, mH, mCount - 1, ERIGHT);
			break;
		case ELEFT:
			new CExplosion(mX - CHIPSIZE * 2, mY, mW, mH, mCount - 1, ELEFT);
			break;
		}
	}
	else if (mFrame > BOMBTIME) {
		mState = EDELETE;
	}
	mFrame++;
}

void CExplosion::Collision(CCharacter* my, CCharacter* yc) {
	if (!mState) return;
	float dx = 0.0f, dy = 0.0f;
	if (CCollision::Collision(my, yc, &dx, &dy)) {
		switch(yc->mTag) {
		case EBLOCK:
			mState = EDELETE;
			break;
		default:
			break;
		}
	}
}

void CExplosion::Render() {
	if (mFrame < BOMBTIME * 0.2f) {
		CRectangle::Render(mX, mY, mW, mH, mpTexture, mU, mU + 16, mV + 16, mV);
	}
	else if (mFrame < BOMBTIME * 0.4f) {
		CRectangle::Render(mX, mY, mW, mH, mpTexture, mU + 16 * 5, mU + 16 * 6, mV + 16, mV);
//		CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 7, 16 * 8, 16 * 7, 16 * 6);
	}
	else if (mFrame < BOMBTIME * 0.6f) {
		CRectangle::Render(mX, mY, mW, mH, mpTexture, mU, mU + 16, mV + 16 * 6, mV + 16 * 5);
//		CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 2, 16 * 3, 16 * 12, 16 * 11);
	}
	else if (mFrame < BOMBTIME) {
		CRectangle::Render(mX, mY, mW, mH, mpTexture, mU + 16 * 5, mU + 16 * 6, mV + 16 * 6, mV + 16 * 5);
//		CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 7, 16 * 8, 16 * 12, 16 * 11);
	}
}
