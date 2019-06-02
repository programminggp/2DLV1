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
	mPriority = 2;
	mTag = ESHOOTPLAYER;
	Enable();
}

void CShootPlayer2::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		Delete();
	}
}

void CShootPlayer2::Collision(CTask& r) {
	CCharacter& c = (CCharacter&)r;
	if (c.mTag == EBOSS) {
		if (CCollision::Collision(*this, c)) {
			//new CEffect(mX, mY + mH, 128, 128);
			//mEffect.mIndex = 0;
			//mEffect.Enable();
			//Disable();
			Delete();
		}
	}
	if (c.mTag == ESHOOTBOSS) {
		if (CCollision::Collision(*this, c)) {
			//new CEffect(mX, mY + mH, 128, 128);
			//mEffect.mIndex = 0;
			//mEffect.Enable();
			//Disable();
			Delete();
		}
	}
}

void CShootPlayer2::Render() {
	CRectangle::Render(&mTexture, 0.0f, 60.0f, 54.0f, 0.0f);
}