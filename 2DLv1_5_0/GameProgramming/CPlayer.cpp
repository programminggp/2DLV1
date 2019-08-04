#include "CPlayer.h"
#include "CUI.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"

#define VELOCITY 4
#define SHOOTINTERVAL 30

CPlayer* CPlayer::mpInstance = 0;;

CPlayer::CPlayer()
	: mShootInterval(0)
	, mFx(0.0f)
	, mFy(0.0f)
{
	mpTexture = &TexBomberman;
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
	mPx = mX;
	mPy = mY;
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
	mX += mFx;
	mY += mFy;
	//Spaceキーが押されているか判定する
	if (mInput.Key(' ') == 1) {
	}
}

void CPlayer::Collision(CCharacter* my, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	float dx = 0.0f, dy = 0.0f;
	if (CCollision::Collision(my, yc, &dx, &dy)) {
		switch(yc->mTag) {
		case EENEMYSHOT:
		case EENEMY:
			new CEffect(mX, mY, 128, 128);
			CUI::mPlayerHit++;
			break;
		case EBLOCK:
			mX += dx;
			mY += dy;
			break;
		default:
			break;
		}
	}
}

void CPlayer::Render() {
	mPx -= mX;
	mPy -= mY;
	if (mPy > 0.0f) {
		int y = mY + 270;
		y /= 20;
		y %= 4;
		switch (y) {
		case 0:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16-1, 0);
			break;
		case 1:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 3, 16 * 4, 16-1, 0);
			break;
		case 2:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16-1, 0);
			break;
		case 3:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 5, 16 * 6, 16-1, 0);
			break;
		}
	}
	else if (mPy < 0.0f) {
		int y = mY + 270;
		y /= 20;
		y %= 4;
		switch (y) {
		case 0:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16*2-1, 16);
			break;
		case 1:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 3, 16 * 4, 16*2-1, 16);
			break;
		case 2:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16*2-1, 16);
			break;
		case 3:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 5, 16 * 6, 16*2-1, 16);
			break;
		}
	}
	else if (mPx > 0.0f) {
		int x = mX + 360;
		x /= 20;
		x %= 4;
		switch (x) {
		case 0:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16-1, 0);
			break;
		case 1:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 0, 16 * 1, 16-1, 0);
			break;
		case 2:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16-1, 0);
			break;
		case 3:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 2, 16 * 3, 16-1, 0);
			break;
		}
	}
	else if (mPx < 0.0f) {
		int x = mX + 360;
		x /= 20;
		x %= 4;
		switch (x) {
		case 0:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16*2-1, 16*1);
			break;
		case 1:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 0, 16 * 1, 16*2-1, 16*1);
			break;
		case 2:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16*2-1, 16*1);
			break;
		case 3:
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 2, 16 * 3, 16*2-1, 16*1);
			break;
		}
	}
	else {
		CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16-1, 0);
	}
}
