#include "CBackGround.h"
#include "CSceneGame.h"
#include "CRectangle.h"

CBackGround::CBackGround() {
	mpTexture = &TexBomberman;
	mTag = EBACKGROUND;
	CSceneGame::mCharacters.push_back(this);
}

CBackGround::CBackGround(float x, float y, float w, float h)
	: CBackGround()
{
	Set(x, y, w, h);
}


void CBackGround::Render() {
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 48.0f, 63.0f, 80.0f, 65.0f);
}