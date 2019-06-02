#include "CEnemy.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"

#define VELOCITY 2

CTexture CEnemy::mTexture;

CEnemy::CEnemy()
	: mVelocity(VELOCITY)
{
	if (mTexture.mId == 0) {
		mTexture.Load("Enemy.tga");
	}
	mPriority = 1;
	mTag = EENEMY;
}

void CEnemy::Update() {
	mY -= mVelocity;
	if (mY < -400) {
		Delete();
	}
}

void CEnemy::Render() {
	CRectangle::Render(&mTexture, 0.0f, 48.0f, 72.0f, 0.0f);
}

void CEnemy::Collision(CTask& r) {
	CCharacter& c = (CCharacter&)r;
	if (c.mTag == ESHOOTPLAYER) {
		if (CCollision::Collision(*this, c)) {
			new CEffect(mX, mY, 128, 128);
			CUI::mEnemyHit++;
			Delete();
		}
	}
}
