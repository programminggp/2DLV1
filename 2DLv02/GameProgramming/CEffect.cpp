#include "CEffect.h"
#include "CTextureManager.h"

CEffect::CEffect()
	: mIndex(0)
{
	SetTexture(&CTextureManager::mEffect);
	mPriority = 3;
	mTag = ENONE;
}

CEffect::CEffect(int posx, int posy, int width, int height)
	: CEffect()
{
	SetXYWH(posx, posy, width, height);
	Enable();
}


void CEffect::Update() {
	if (mIndex == 20) {
		mIndex = 0;
		Delete();
	}
}

void CEffect::Render() {
	CRectangle::Render(mIndex++);
}

