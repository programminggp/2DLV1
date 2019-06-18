#include "CShootPlayer.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"
#include "CTextureManager.h"

#define VELOCITY 10

CShootPlayer::CShootPlayer()
{
	mpTexture = &CTextureManager::mTexture;
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
		mState = EDISABLED;
	}
}

void CShootPlayer::Collision(CCharacter* my, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	CCharacter& c = (CCharacter&)*yc;
	if (CCollision::Collision(*this, c)) {
		switch(yc->mTag) {
		case EENEMY:
		case ESHOOTENEMY:
			mState = ECOLLISION;
			break;
		default:
			break;
		}
	}
}

void CShootPlayer::Render() {
	CRectangle::Render(mpTexture, 10.0f, 34.0f, 350.0f, 284.0f);
}