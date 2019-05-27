#include "CEffect.h"

CTexture CEffect::mTexture;

CEffect::CEffect()
	: mIndex(0)
{
	mpTexture = &mTexture;
	mPriority = 3;
	mTag = ENONE;
}

CEffect::CEffect(int posx, int posy, int width, int height)
	: CEffect()
{
	SetXYWH(posx, posy, width, height);
//	Enable();
}


void CEffect::Update() {
	if (mIndex == 20) {
		mIndex = 0;
		//Disable();
		Delete();
	}
}

void CEffect::Render() {
	CRectangle::Render(mIndex++);
}

