#include "CShootEnemy.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"
#include "CTextureManager.h"

#define VELOCITY 10

CShootEnemy::CShootEnemy()
{
	mpTexture = &CTextureManager::mShoot;
	mTag = ESHOOTENEMY;
	CSceneGame::mCharacters.push_back(this);
}

CShootEnemy::CShootEnemy(float x, float y, float w, float h)
: CShootEnemy()
{
	Set(x, y, w, h);
}


void CShootEnemy::Update() {
	mY -= VELOCITY;
	if (mY < -300 - mH) {
		mEnabled = false;
	}
}

void CShootEnemy::Collision(CCharacter* my, CCharacter* you) {
	if (!mEnabled) return;
	if (!you->mEnabled) return;
	CCharacter& c = (CCharacter&)*you;
	if (c.mTag == EPLAYER) {
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY + mH, 128, 128);
			mEnabled = false;
		}
	}
	if (c.mTag == ESHOOTPLAYER) {
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY + mH, 128, 128);
			mEnabled = false;
		}
	}
}

void CShootEnemy::Render() {
	CRectangle::Render(mpTexture, 10.0f, 34.0f, 176.0f, 240.0f);
}