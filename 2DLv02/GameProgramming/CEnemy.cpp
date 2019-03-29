#include "CEnemy.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"
#include "CTextureManager.h"

#define VELOCITY 2

CEnemy::CEnemy()
	: mVelocity(VELOCITY)
{
	SetPosition(0, 300);
	SetSize(48, 72);
	SetTexture(&CTextureManager::mEnemy);
	mPriority = 1;
	mTag = EENEMY;
	Enable();
}

void CEnemy::Update() {
	mY -= mVelocity;
	if (mY < -400) {
		Delete();
	}
}

void CEnemy::Render() {
	CRectangle::Render();
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
