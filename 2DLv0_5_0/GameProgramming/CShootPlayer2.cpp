#include "CShootPlayer2.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CTextureManager.h"

#define VELOCITY 10

CShootPlayer2::CShootPlayer2()
{
	mpTexture = &CTextureManager::mTexture;
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
			mState = ECOLLISION;
		}
	}
	if (c.mTag == EBOSS) {
		if (CCollision::Collision(*this, c)) {
			mState = ECOLLISION;
		}
	}
	if (c.mTag == ESHOOTBOSS) {
		if (CCollision::Collision(*this, c)) {
			mState = ECOLLISION;
		}
	}
}

void CShootPlayer2::Render() {
	CRectangle::Render(mpTexture, 0.0f, 60.0f, 54.0f, 0.0f);
}