#include "CShootPlayer2.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"
#include "CRectangle.h"

#define VELOCITY 10

CShootPlayer2::CShootPlayer2()
{
	mpTexture = &TexShoot;
	mTag = ESHOOTPLAYER;
}

void CShootPlayer2::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		mState = EDISABLED;
	}
}

void CShootPlayer2::Collision(CCharacter* my, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	CCharacter& c = (CCharacter&)*yc;
	if (c.mTag == EENEMY) {
		if (CCollision::Collision(*this, c)) {
			mState = EDISABLED;
		}
	}
	if (c.mTag == EBOSS) {
		if (CCollision::Collision(*this, c)) {
			mState = EDISABLED;
		}
	}
	if (c.mTag == ESHOOTBOSS) {
		if (CCollision::Collision(*this, c)) {
			mState = EDISABLED;
		}
	}
}

void CShootPlayer2::Render() {
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 0.0f, 60.0f, 54.0f, 0.0f);
}