#include "CShootPlayer2.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CTextureManager.h"

#define VELOCITY 10

CShootPlayer2::CShootPlayer2()
{
	mpTexture = &CTextureManager::mShoot;
	mTag = ESHOOTPLAYER;
}

void CShootPlayer2::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		mEnabled = false;
	}
}

void CShootPlayer2::Collision(CCharacter* my, CCharacter* you) {
	CCharacter& c = (CCharacter&)*you;
	if (c.mTag == EENEMY) {
		if (CCollision::Collision(*this, c)) {
			//			new CEffect(mX, mY + mH, 128, 128);
			mEnabled = false;
		}
	}
	if (c.mTag == EBOSS) {
		if (CCollision::Collision(*this, c)) {
			//			new CEffect(mX, mY + mH, 128, 128);
			mEnabled = false;
		}
	}
	if (c.mTag == ESHOOTBOSS) {
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY + mH, 128, 128);
			mEnabled = false;
		}
	}
}

void CShootPlayer2::Render() {
	CRectangle::Render(mpTexture, 0.0f, 60.0f, 54.0f, 0.0f);
}