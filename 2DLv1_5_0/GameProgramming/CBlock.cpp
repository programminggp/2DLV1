#include "CBlock.h"
#include "CSceneGame.h"
#include "CRectangle.h"

CBlock::CBlock() {
	mpTexture = &TexBomberman;
	mTag = EBLOCK;
	CSceneGame::mCharacters.push_back(this);
}

CBlock::CBlock(float x, float y, float w, float h)
:CBlock()
{
	Set(x, y, w, h);
}

void CBlock::Render() {
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 48.0f, 63.0f, 63.0f, 48.0f);
}
