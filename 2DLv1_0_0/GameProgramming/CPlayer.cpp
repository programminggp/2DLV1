#include "CPlayer.h"
#include "CRectangle.h"
#include "CCollision.h"
#include "CSceneGame.h"
#include "CPlayerShot.h"
#include "CEffect.h"

#define VELOCITY 5
#define SHOOTINTERVAL 30

CPlayer* CPlayer::mpInstance = 0;;

CPlayer::CPlayer()
	: mShot(0)
	, mpTexture(0)
{
	mTag = EPLAYER;
	mpInstance = this;
}


CPlayer::CPlayer(float x, float y, float w, float h)
	: CPlayer()
{
	Set(x, y, w, h);
}


void CPlayer::Update() {
	if (mState == EDISABLED) mState = EDISABLED;
	if (!mState) return;

	if (mShot > 0) {
		mShot--;
	}
	//Sキーが押されているか判定する
	if (mInput.Key('S') == 1) {
		//四角形を下へ移動させる
		mY -= VELOCITY;
	}
	//Wキーが押されているか判定する
	if (mInput.Key('W') == 1) {
		//四角形を上へ移動させる
		mY += VELOCITY;
	}
	//Aキーが押されているか判定する
	if (mInput.Key('A') == 1) {
		//四角形を左へ移動させる
		mX -= VELOCITY;
	}
	//Dキーが押されているか判定する
	if (mInput.Key('D') == 1) {
		//四角形を右へ移動させる
		mX += VELOCITY;
	}
	//Spaceキーが押されているか判定する
	if (mInput.Key(' ') == 1) {
		if (mShot == 0) {
			mShot = SHOOTINTERVAL;
			//弾を発射する
			for (int i = 0; i < 5; i++) {
				if (CPlayerShot::mShot[i].mState == EDELETE) {
					CPlayerShot::mShot[i].Set(mX, mY, 12, 32);
					CPlayerShot::mShot[i].mState = EENABLED;
					break;
				}
			}
		}
	}
	mEffect.Update();
}

void CPlayer::Collision(CCharacter* mc, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	if (CCollision::Collision(this, yc)) {
		switch(yc->mTag) {
		case EENEMYSHOT:
		case EENEMY:
			mEffect.Set(mX, mY, 64, 64);
			mEffect.mState = EENABLED;
			//for (int i = 0; i < 5; i++) {
			//	if (CEffect::mEffect[i].mState == EDELETE) {
			//		CEffect::mEffect[i].Set(mX, mY, 64, 64);
			//		CEffect::mEffect[i].mState = EENABLED;
			//		break;
			//	}
			//}
			//new CEffect(mX, mY, 64, 64);
			//CUI::mPlayerHit++;
			break;
		default:
			break;
		}
	}
}

void CPlayer::Render() {
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 0.0f, 74.0f, 88.0f, 0.0f);
	mEffect.Render();
}
