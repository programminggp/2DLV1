#include "CShootPlayer.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"
#include "CTextureManager.h"

#define VELOCITY 10

CShootPlayer::CShootPlayer()
{
	mpTexture = &CTextureManager::mShoot;
	mTag = ESHOOTPLAYER;
	CSceneGame::mCharacters.push_back(this);
}

CShootPlayer::CShootPlayer(float x, float y, float w, float h)
	: CShootPlayer()
{
	Set(x, y, w, h);
}


void CShootPlayer::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		mEnabled = false;
	}
}

void CShootPlayer::Collision(CCharacter* my, CCharacter* you) {
	if (!mEnabled) return;
	CCharacter& c = (CCharacter&)*you;
	if (c.mTag == EENEMY) {
		if (!you->mEnabled) return;
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY + mH, 128, 128);
			mEnabled = false;
		}
	}
	if (c.mTag == ESHOOTENEMY) {
		if (CCollision::Collision(*this, c)) {
//			new CEffect(mX, mY + mH, 128, 128);
			mEnabled = false;
		}
	}
}

void CShootPlayer::Render() {
	CRectangle::Render(mpTexture, 10.0f, 34.0f, 350.0f, 284.0f);
}