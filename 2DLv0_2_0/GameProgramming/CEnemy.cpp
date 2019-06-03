#include "CEnemy.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"
#include "CShootEnemy.h"

#define VELOCITY 4

CTexture CEnemy::mTexture;

CEnemy::CEnemy()
	: mVelocity(VELOCITY)
	, mFire(0)
{
	if (mTexture.mId == 0) {
		mTexture.Load("Enemy.tga");
	}
	mTag = EENEMY;
}

CEnemy::CEnemy(float x, float y, float w, float h)
	: CEnemy()
{
	Set(x, y, w, h);
}


void CEnemy::Update() {
	mFire++;
	if (mFire % 50 == 0) {
		mFire = 0;
		new CShootEnemy(mX, mY, 24, 64);
	}
	if (mX > 400) {
		mVelocity *= -1;
		mY -= mH * 2;
	}
	else if (mX < -400) {
		mVelocity *= -1;
		mY -= mH * 2;
	}
	mX += mVelocity;
	if (mY < -400) {
		mState = EDELETE;
	}
}

void CEnemy::Render() {
	CRectangle::Render(&mTexture, 0.0f, 48.0f, 72.0f, 0.0f);
}

void CEnemy::Collision(CCharacter* my, CCharacter* you) {
	CCharacter& c = (CCharacter&)*you;
	if (c.mTag == ESHOOTPLAYER) {
		if (CCollision::Collision(*this, c)) {
			new CEffect(mX, mY, 128, 128);
			CUI::mEnemyHit++;
			mState = EDELETE;
		}
	}
}
