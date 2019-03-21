#include "CPlayer.h"
#include "CShootPlayer2.h"

#define VELOCITY 5

CPlayer* CPlayer::mpInstance = 0;;


CPlayer::CPlayer()
	: mHit(0)
	, mFont("Font.tga", 1, 64, 16, 33)
{
	LoadTexture("Player.tga");
	mPriority = 1;
	mTag = EPLAYER;
	Enable();
	mpInstance = this;
}

void CPlayer::Update() {
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
		if (mShoot.mStatus != EENABLED) {
			//弾を発射する
//			mShoot.SetXYWH(mX, mY, 60, 54);
//			mShoot.Enable();
		}
		//弾を発射する
		CShootPlayer2 *s = new CShootPlayer2();
		s->SetXYWH(mX, mY, 60, 54);
	}
	mEffect.SetXYWH(mX, mY, 128, 128);
}

void CPlayer::Collision(CTask& r) {
	CCharacter& c = (CCharacter&)r;
	if (c.mTag == ESHOOTBOSS) {
		if (CCollision::Collision(*this, c)) {
			mEffect.mIndex = 0;
			mEffect.Enable();
			mHit++;
		}
	}
	if (c.mTag == EBOSS) {
		if (CCollision::Collision(*this, c)) {
//			mEffect.mIndex = 0;
			mEffect.Enable();
			mHit++;
		}
	}
}

void CPlayer::Render() {
	CRectangle::Render();
	char buf[10];
	sprintf(buf, "%d", mHit);
	mFont.Render(buf, mX + mW, mY - mH, 24, 32);
}
