#include "CPlayer.h"
#include "CUI.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"
#include "CBomb.h"
#include "Define.h"

CPlayer* CPlayer::mpInstance = 0;;

CPlayer::CPlayer()
	: mShootInterval(0)
	, mFx(0.0f)
	, mFy(0.0f)
	, mIsAlive(true)
	, mFrame(0)
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

	if (mIsAlive) {
		if (mShootInterval > 0) {
			mShootInterval--;
		}
		else {
			//Spaceキーが押されているか判定する
			//4　爆弾配置
			if (mInput.Key(VK_SPACE) == 1) {
				mShootInterval = SHOOTINTERVAL;
				new CBomb(mX, mY, CHIPSIZE, CHIPSIZE);
			}
		}

		mPx = mX;
		mPy = mY;
		mFx = mFy = 0.0f;

		//Sキーが押されているか判定する
		if (mInput.Key('S') == 1) {
			//四角形を下へ移動させる
			mFy -= VELOCITY_P;
		}
		//3 プレイヤー移動
		//Wキーが押されているか判定する
		if (mInput.Key('W') == 1) {
			//四角形を上へ移動させる
			mFy += VELOCITY_P;
		}
		//Aキーが押されているか判定する
		if (mInput.Key('A') == 1) {
			//四角形を左へ移動させる
			mFx -= VELOCITY_P;
		}
		//Dキーが押されているか判定する
		if (mInput.Key('D') == 1) {
			//四角形を右へ移動させる
			mFx += VELOCITY_P;
		}
		mX += mFx;
		mY += mFy;
	}
	else {
		if (mFrame > 70) {
			mState = EDELETE;
		}
		mFrame++;
	}
}

void CPlayer::Collision(CCharacter* my, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	if (!mIsAlive) return;
	float dx = 0.0f, dy = 0.0f;
	if (CCollision::Collision(my, yc, &dx, &dy)) {
		switch(yc->mTag) {
		case EBLOCK:
		case EBOMB:
			mX += dx;
			mY += dy;
			break;
		//9　敵爆発衝突
		case EEXPLOSION:
		case EENEMY:
			mTag = EBACKGROUND;
			mIsAlive = false;
			mFrame = 0;
			break;
		default:
			break;
		}
	}
}

void CPlayer::Render() {
	if (mIsAlive) {
		mPx -= mX;
		mPy -= mY;
		if (mPy > 0.0f) {
			int y = -mY;
			y /= 20;
			y %= 4;
			switch (y) {
			case 0:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16 - 1, 0.5f);
				break;
			case 1:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 3, 16 * 4, 16 - 1, 0.5f);
				break;
			case 2:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16 - 1, 0.5f);
				break;
			case 3:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 5, 16 * 6, 16 - 1, 0.5f);
				break;
			}
		}
		else if (mPy < 0.0f) {
			int y = -mY;
			y /= 20;
			y %= 4;
			switch (y) {
			case 0:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16 * 2 - 1, 16);
				break;
			case 1:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 3, 16 * 4, 16 * 2 - 1, 16);
				break;
			case 2:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16 * 2 - 1, 16);
				break;
			case 3:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 5, 16 * 6, 16 * 2 - 1, 16);
				break;
			}
		}
		else if (mPx > 0.0f) {
			int x = mX;
			x /= 20;
			x %= 4;
			switch (x) {
			case 0:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16 - 1, 0.5f);
				break;
			case 1:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 0, 16 * 1, 16 - 1, 0.5f);
				break;
			case 2:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16 - 1, 0.5f);
				break;
			case 3:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 2, 16 * 3, 16 - 1, 0.5f);
				break;
			}
		}
		else if (mPx < 0.0f) {
			int x = mX;
			x /= 20;
			x %= 4;
			switch (x) {
			case 0:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16 * 2 - 1, 16 * 1);
				break;
			case 1:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 0, 16 * 1, 16 * 2 - 1, 16 * 1);
				break;
			case 2:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16 * 2 - 1, 16 * 1);
				break;
			case 3:
				CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 2, 16 * 3, 16 * 2 - 1, 16 * 1);
				break;
			}
		}
		else {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16 - 1, 0.5f);
		}
	}
	else {
		if (mFrame / 10 == 0) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 0, 16 * 1, 16 * 3, 16 * 2);
		}
		else if (mFrame / 10 == 1) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 1, 16 * 2, 16 * 3, 16 * 2);
		}
		else if (mFrame / 10 == 2) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 2, 16 * 3, 16 * 3, 16 * 2 + 1);
		}
		else if (mFrame / 10 == 3) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 3, 16 * 4, 16 * 3, 16 * 2 + 1);
		}
		else if (mFrame / 10 == 4) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 4, 16 * 5, 16 * 3, 16 * 2 + 1);
		}
		else if (mFrame / 10 == 5) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 5, 16 * 6, 16 * 3, 16 * 2 + 1);
		}
		else if (mFrame / 10 == 6) {
			CRectangle::Render(mX, mY, mW, mH, mpTexture, 16 * 6, 16 * 7, 16 * 3, 16 * 2 + 1);
		}
	}
}
