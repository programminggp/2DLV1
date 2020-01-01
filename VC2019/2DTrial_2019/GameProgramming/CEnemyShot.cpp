#include "CEnemyShot.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"
#include "CRectangle.h"

#define VELOCITY 5

CEnemyShot CEnemyShot::mShot[5];

CEnemyShot::CEnemyShot()
{
	mTag = EENEMYSHOT;
	mState = EDELETE;

}

CEnemyShot::CEnemyShot(float x, float y, float w, float h)
: CEnemyShot()
{
	Set(x, y, w, h);
}


void CEnemyShot::Update() {
	mY -= VELOCITY;
	if (mY <  -mH) {
		mState = EDELETE;
	}
}

void CEnemyShot::Collision(CCharacter* mc, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	if (CCollision::Collision(this, yc)) {
		switch(yc->mTag) {
		case EPLAYER:
		case EPLAYERSHOT:
			mState = EDISABLED;
			break;
		default:
			break;
		}
	}
}

void CEnemyShot::Render() {
	if (!mState) return;
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 10.0f, 34.0f, 176.0f, 240.0f);
}