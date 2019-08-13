#include "CBomb.h"
#include "CRectangle.h"
#include "CCollision.h"
#include "CSceneGame.h"
#include "CExplosion.h"

#define BOMBTIME (60 * 3)

CBomb::CBomb()
	: mFrame(0)
{
	mpTexture = &TexBomberman;
//	mTag = EBOMB;
	mTag = EBACKGROUND;
	CSceneGame::mCharacters.push_back(this);
}


CBomb::CBomb(float x, float y, float w, float h)
	: CBomb()
{
	Set(x, y, w, h);
}

void CBomb::Update() {
	mFrame++;
	if (mFrame > BOMBTIME) {
		new CExplosion(mX, mY, mW, mH, 2);
		mState = EDELETE;
	}
}

void CBomb::Collision(CCharacter* my, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	float dx = 0.0f, dy = 0.0f;
	if (CCollision::Collision(my, yc, &dx, &dy)) {
		switch(yc->mTag) {
		case EBOMB:
			yc->mState = EDELETE;
			break;
		case EBLOCK:
			mX += dx;
			mY += dy;
			break;
		case EPLAYER:
			break;
		case EEXPLOSION:
			new CExplosion(mX, mY, mW, mH, 2);
			mState = EDELETE;
			break;
		default:
			mTag = EBOMB;
			break;
		}
	}
}

void CBomb::Render() {
	int f = mFrame / 20;
	f %= 4;
	switch (f) {
	case 0:
		CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 0, 16 * 1, 16 * 4, 16 * 3);
		break;
	case 1:
		CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16 * 4, 16 * 3);
		break;
	case 2:
		CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 2, 16 * 3 - 1, 16 * 4, 16 * 3);
		break;
	case 3:
		CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16 * 4, 16 * 3);
		break;
	}
}
