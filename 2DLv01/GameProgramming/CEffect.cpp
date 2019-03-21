#include "CEffect.h"

CEffect::CEffect()
	: mIndex(0)
{
	LoadTexture("BossExplosion.tga", 4, 5);
	mPriority = 3;
	mTag = ENONE;
}

void CEffect::Update() {
	if (mIndex == 20) {
		mIndex = 0;
		Disable();
	}
}

void CEffect::Render() {
	CRectangle::Render(mIndex++);
}

