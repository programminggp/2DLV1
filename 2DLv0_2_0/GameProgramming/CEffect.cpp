#include "CEffect.h"

CTexture CEffect::mTexture;

CEffect::CEffect()
	: mIndex(0)
{
	if (mTexture.mId == 0) {
		mTexture.Load("BossExplosion.tga");
	}
	mPriority = 3;
	mTag = ENONE;
}

CEffect::CEffect(int posx, int posy, int width, int height)
	: CEffect()
{
	SetXYWH(posx, posy, width, height);
}


void CEffect::Update() {
	if (mIndex++ == 20) {
		mIndex = 0;
		Delete();
	}
}

void CEffect::Render() {
	int row = mIndex / 5 + 1;
	int col = mIndex % 5;
	CRectangle::Render(&mTexture,
		mTexture.mHeader.width * col++ / 5.0f,
		mTexture.mHeader.width * col / 5.0f,
		mTexture.mHeader.height * row-- / 4.0f,
		mTexture.mHeader.height * row / 4.0f);
}

