#include "CEffect.h"
#include "CTextureManager.h"
#include "CSceneGame.h"


CEffect::CEffect()
	: mIndex(0)
{
	mpTexture = &CTextureManager::mTexture;
	mTag = ENONE;
	CSceneGame::mCharacters.push_back(this);
}

CEffect::CEffect(float x, float y, float w, float h)
	: CEffect()
{
	SetXYWH(x, y, w, h);
}


void CEffect::Update() {
	if (mIndex++ == 20) {
		mIndex = 0;
		mState = EDISABLED;
	}
}

void CEffect::Render() {
	int row = mIndex / 5;
	int col = mIndex % 5;
	CRectangle::Render(mpTexture,
		mpTexture->mHeader.width * col / 5.0f,
		mpTexture->mHeader.width * (col + 1) / 5.0f,
		mpTexture->mHeader.height * (row - 1) / 4.0f,
		mpTexture->mHeader.height * row / 4.0f);
}

