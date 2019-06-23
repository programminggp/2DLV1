#include "CPlayer.h"
#include "CShootPlayer.h"
#include "CShootPlayer2.h"
#include "CUI.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CTextureManager.h"
#include "CSceneGame.h"

#define VELOCITY 5
#define SHOOTINTERVAL 30

CPlayer* CPlayer::mpInstance = 0;;

CPlayer::CPlayer()
	: mShootInterval(0)
	, mFx(0.0f)
	, mFy(0.0f)
	, mJump(true)
	, mVolocityY(0.0f)
{
	mpTexture = &TexPlayer;
	mTag = EPLAYER;
	mpInstance = this;
	CSceneGame::mCharacters.push_back(this);
}


CPlayer::CPlayer(float x, float y, float w, float h)
	: CPlayer()
{
	Set(x, y, w, h);
}


void CPlayer::Update() {
	if (mState == ECOLLISION) mState = EDISABLED;
	if (!mState) return;

	mFx = mFy = 0.0f;

	if (mShootInterval > 0) {
		mShootInterval--;
	}
	//Sキーが押されているか判定する
	if (mInput.Key('S') == 1) {
		//四角形を下へ移動させる
		mFy -= VELOCITY;
	}
	//Wキーが押されているか判定する
	if (mInput.Key('W') == 1) {
		//四角形を上へ移動させる
		mFy += VELOCITY;
	}
	//Aキーが押されているか判定する
	if (mInput.Key('A') == 1) {
		//四角形を左へ移動させる
		mFx -= VELOCITY;
	}
	//Dキーが押されているか判定する
	if (mInput.Key('D') == 1) {
		//四角形を右へ移動させる
		mFx += VELOCITY;
	}
	if (mJump) {
		//Spaceキーが押されているか判定する
		if (mInput.Key(' ') == 1) {
			mJump = false;
			mVolocityY = 30;
		}
	}
	mVolocityY -= 2.0f;
	mX += mFx;
	mY += mFy + mVolocityY;
}

void CPlayer::Collision(CCharacter* my, CCharacter* yc) {
	float x = 0.0f, y = 0.0f;
	if (!mState) return;
	if (!yc->mState) return;
	switch (yc->mTag) {
	case EGROUND:
		if (CCollision::Collision(*this, *yc, &x, &y)) {
			if (y != 0.0f) {
				mVolocityY = 0.0f;
			}
			mJump = true;
			mX += x;
			mY += y;
		}
		break;
	case ESHOOTENEMY:
	case EENEMY:
		if (CCollision::Collision(*this, *yc)) {
			new CEffect(mX, mY, 128, 128);
			CUI::mPlayerHit++;
		}
		break;
	}
}

void CPlayer::Render() {
	if ((int)(mX + 400) % 72 < 36) {
		CRectangle::Render(mpTexture, 0.0f, 72.0f, 88.0f, 0.0f);
	}
	else {
		CRectangle::Render(mpTexture, 72.0f, 144.0f, 88.0f, 0.0f);
	}
}
