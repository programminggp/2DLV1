#include "CEffect.h"

CTexture CEffect::mTexture;

CEffect::CEffect()
	: mIndex(0)
{
	if (mTexture.mId == 0) {
		mTexture.Load("BossExplosion.tga");
	}
//	mPriority = 3;
	mTag = ENONE;
}

CEffect::CEffect(float x, float y, float w, float h)
	: CEffect()
{
	SetXYWH(x, y, w, h);
}


void CEffect::Update() {
	if (mIndex++ == 20) {
		mIndex = 0;
		mState = EDELETE;
//		Delete();
	}
}

void CEffect::Render() {
	int row = mIndex / 5;
	int col = mIndex % 5;
	CRectangle::Render(&mTexture,
		mTexture.mHeader.width * col / 5.0f,
		mTexture.mHeader.width * (col + 1) / 5.0f,
		mTexture.mHeader.height * (row - 1) / 4.0f,
		mTexture.mHeader.height * row / 4.0f);
}

