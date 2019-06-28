#include "CPlayerShot2.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"
#include "CRectangle.h"

#define VELOCITY 10

CPlayerShot2::CPlayerShot2()
{
	mTag = EPLAYERSHOT;
}

void CPlayerShot2::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		mState = EDISABLED;
	}
}

void CPlayerShot2::Collision(CCharacter* mc, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	if (yc->mTag == EENEMY) {
		if (CCollision::Collision(this, yc)) {
			mState = EDISABLED;
		}
	}
	else if (yc->mTag == EBOSS) {
		if (CCollision::Collision(this, yc)) {
			mState = EDISABLED;
		}
	}
	if (yc->mTag == ESHOOTBOSS) {
		if (CCollision::Collision(this, yc)) {
			mState = EDISABLED;
		}
	}
}

void CPlayerShot2::Render() {
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 0.0f, 60.0f, 54.0f, 0.0f);
}