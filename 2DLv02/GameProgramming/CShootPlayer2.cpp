#include "CShootPlayer2.h"
#include "CCollision.h"
#include "CEffect.h"
#include "CTextureManager.h"

#define VELOCITY 10

CShootPlayer2::CShootPlayer2()
{
	SetTexture(&CTextureManager::mShootPlayer);
	mPriority = 2;
	mTag = ESHOOTPLAYER;
	Enable();
}

CShootPlayer2::CShootPlayer2(float x, float y, float w, float h) 
: CShootPlayer2()
{
	SetPosition(x, y);
	SetSize(w, h);
}


void CShootPlayer2::Update() {
	mY += VELOCITY;
	if (mY > 300 + mH) {
		Delete();
	}
}

void CShootPlayer2::Collision(CTask& r) {
	CCharacter& c = (CCharacter&)r;
	if (c.mTag == EBOSS) {
		if (CCollision::Collision(*this, c)) {
			Delete();
		}
	}
	if (c.mTag == ESHOOTBOSS) {
		if (CCollision::Collision(*this, c)) {
			Delete();
		}
	}
}
