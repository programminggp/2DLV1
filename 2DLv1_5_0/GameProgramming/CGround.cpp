#include "CGround.h"
#include "CSceneGame.h"
#include "CRectangle.h"

CGround::CGround() {
	mpTexture = &TexBomberman;
	mTag = EBACKGROUND;
	CSceneGame::mCharacters.push_back(this);
}

CGround::CGround(float x, float y, float w, float h)
	: CGround()
{
	Set(x, y, w, h);
}


void CGround::Render() {
	CRectangle::Render(mX, mY, mW, mH, mpTexture, 85.0f, 121.0f, 38.0f, 0.0f);
}