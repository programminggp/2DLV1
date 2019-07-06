#include "CEffect.h"
#include "CSceneGame.h"
#include "CRectangle.h"

//CEffect CEffect::mEffect[5];

CEffect::CEffect()
	: mIndex(0)
{
	mTag = ENONE;
	mState = EDELETE;
}

CEffect::CEffect(float x, float y, float w, float h)
	: CEffect()
{
	Set(x, y, w, h);
}


void CEffect::Update() {
	if (!mState) return;
	if (mIndex++ == 20) {
		mIndex = 0;
		mState = EDELETE;
	}
}

void CEffect::Render() {
	if (!mState) return;
	int row = mIndex / 5;
	int col = mIndex % 5;
	CRectangle::Render(mX, mY, mW, mH, mpTexture,
		mpTexture->mHeader.width * col / 5.0f,
		mpTexture->mHeader.width * (col + 1) / 5.0f,
		mpTexture->mHeader.height * (row - 1) / 4.0f,
		mpTexture->mHeader.height * row / 4.0f);
}

