#include "CBlock.h"
#include "CTextureManager.h"
#include "CSceneGame.h"

CBlock::CBlock() {
	mpTexture = &CTextureManager::mTexture;
	mTag = EBLOCK;
	CSceneGame::mCharacters.push_back(this);
}

CBlock::CBlock(float x, float y, float w, float h)
:CBlock()
{
	Set(x, y, w, h);
}

void CBlock::Render() {
	CRectangle::Render(mpTexture, 48.0f, 63.0f, 63.0f, 48.0f);
}
