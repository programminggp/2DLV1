#include "CBackGround.h"
#include "CTextureManager.h"
#include "CSceneGame.h"

CBackGround::CBackGround() {
	mpTexture = &CTextureManager::mTexture;
	mTag = EBACKGROUND;
	CSceneGame::mCharacters.push_back(this);
}

CBackGround::CBackGround(float x, float y, float w, float h)
	: CBackGround()
{
	Set(x, y, w, h);
}


void CBackGround::Render() {
	CRectangle::Render(mpTexture, 48.0f, 63.0f, 80.0f, 65.0f);
}