#include "CPlayerShot.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"
#include "CRectangle.h"

#define VELOCITY 10

CPlayerShot CPlayerShot::mShot[5];

CPlayerShot::CPlayerShot()
{
	mTag = EPLAYERSHOT;
	mState = EDELETE;
}

CPlayerShot::CPlayerShot(float x, float y, float w, float h)
	: CPlayerShot()
{
	Set(x, y, w, h);
}


void CPlayerShot::Update() {
	mY += VELOCITY;
	if (mY > 600 + mH) {
		mState = EDELETE;
	}
}

void CPlayerShot::Collision(CCharacter* my, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	if (CCollision::Collision(this, yc)) {
		switch(yc->mTag) {
		case EENEMY:
		case EENEMYSHOT:
			mState = EDISABLED;
			break;
		default:
			break;
		}
	}
}

void CPlayerShot::Render() {
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 10.0f, 34.0f, 350.0f, 284.0f);
}