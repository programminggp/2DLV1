#include "CShootPlayer.h"
#include "CCollision.h"
#include "CEffect.h"

#define VELOCITY 10

CTexture CShootPlayer::mTexture;

CShootPlayer::CShootPlayer()
{
	if (mTexture.mId == 0) {
		mTexture.Load("Shoot.tga");
	}
	mTag = ESHOOTPLAYER;
}

CShootPlayer::CShootPlayer(float x, float y, float w, float h)
	: CShootPlayer()
{
	Set(x, y, w, h);
}


void CShootPlayer::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		mState = EDELETE;
	}
}

void CShootPlayer::Collision(CCharacter* my, CCharacter* you) {
	CCharacter& c = (CCharacter&)*you;
	if (c.mTag == EENEMY) {
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY + mH, 128, 128);
			mState = EDELETE;
		}
	}
	if (c.mTag == ESHOOTENEMY) {
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY + mH, 128, 128);
			mState = EDELETE;
		}
	}
}

void CShootPlayer::Render() {
	CRectangle::Render(&mTexture, 10.0f, 34.0f, 350.0f, 284.0f);
}