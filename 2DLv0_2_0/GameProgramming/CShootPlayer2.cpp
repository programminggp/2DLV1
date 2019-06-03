#include "CShootPlayer2.h"
#include "CCollision.h"
#include "CEffect.h"

#define VELOCITY 10

CTexture CShootPlayer2::mTexture;

CShootPlayer2::CShootPlayer2()
{
	if (mTexture.mId == 0) {
		mTexture.Load("ShootPlayer.tga");
	}
	mTag = ESHOOTPLAYER;
}

void CShootPlayer2::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		mState = EDELETE;
	}
}

void CShootPlayer2::Collision(CCharacter* my, CCharacter* you) {
	CCharacter& c = (CCharacter&)*you;
	if (c.mTag == EENEMY) {
		if (CCollision::Collision(*this, c)) {
			//			new CEffect(mX, mY + mH, 128, 128);
			mState = EDELETE;
		}
	}
	if (c.mTag == EBOSS) {
		if (CCollision::Collision(*this, c)) {
			//			new CEffect(mX, mY + mH, 128, 128);
			mState = EDELETE;
		}
	}
	if (c.mTag == ESHOOTBOSS) {
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY + mH, 128, 128);
			mState = EDELETE;
		}
	}
}

void CShootPlayer2::Render() {
	CRectangle::Render(&mTexture, 0.0f, 60.0f, 54.0f, 0.0f);
}