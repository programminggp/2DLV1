#include "CBoss.h"
#include "CPlayer.h"
#include "CCollision.h"
#include "CUI.h"
#include "CEffect.h"
#include "CSceneGame.h"

#define VELOCITY 2

CBoss::CBoss()
	: mVelocity(VELOCITY)
{
	mTag = EBOSS;
}

CBoss::CBoss(float x, float y, float w, float h)
	: CBoss()
{
	Set(x, y, w, h);
}


void CBoss::Update() {
	mX += mVelocity;
	if (mX > 800 - mW || mX < 0 + mW) {
		mVelocity *= -1;
	}
	mEffect.Update();
}

void CBoss::Render() {
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 0.0f, 159.0f, 240.0f, 0.0f);
	mEffect.Render();
}

void CBoss::Collision(CCharacter* mc, CCharacter* yc) {
	if (yc->mTag == EPLAYERSHOT) {
		if (CCollision::Collision(this, yc)) {
			if (mEffect.mState == EDELETE) {
				mEffect.Set(yc->mX, mY, 128, 128);
				mEffect.mState = EENABLED;
			}
		}
	}
}
