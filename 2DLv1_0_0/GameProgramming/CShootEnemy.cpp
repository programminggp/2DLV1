#include "CShootEnemy.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CSceneGame.h"
#include "CRectangle.h"

#define VELOCITY 10

CShootEnemy::CShootEnemy()
{
	mpTexture = &TexShoot;
	mTag = ESHOOTENEMY;
}

CShootEnemy::CShootEnemy(float x, float y, float w, float h)
: CShootEnemy()
{
	Set(x, y, w, h);
}


void CShootEnemy::Update() {
	mY -= VELOCITY;
	if (mY < -300 - mH) {
		mState = EDISABLED;
	}
}

void CShootEnemy::Collision(CCharacter* my, CCharacter* yc) {
	if (!mState) return;
	if (!yc->mState) return;
	CCharacter& c = (CCharacter&)*yc;
	if (CCollision::Collision(*this, c)) {
		switch(c.mTag) {
		case EPLAYER:
		case ESHOOTPLAYER:
			mState = EDISABLED;
			break;
		default:
			break;
		}
	}
}

void CShootEnemy::Render() {
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 10.0f, 34.0f, 176.0f, 240.0f);
}