#include "CBackGround.h"
#include "CTextureManager.h"
#include "CSceneGame.h"

CBackGround::CBackGround() {
	mpTexture = &TexBG;
	mTag = EBACKGROUND;
	CSceneGame::mCharacters.push_back(this);
}

CBackGround::CBackGround(float x, float y, float w, float h)
	: CBackGround()
{
	Set(x, y, w, h);
}


void CBackGround::Render() {
	CRectangle::Render(mpTexture, 0.0f, 1000.0f, 750.0f, 0.0f);
}