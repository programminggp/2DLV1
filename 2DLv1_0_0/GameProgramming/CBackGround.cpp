#include "CBackGround.h"
#include "CSceneGame.h"

CBackGround::CBackGround() {
	mpTexture = &TexBackGround;
	mTag = EBACKGROUND;
}

CBackGround::CBackGround(float x, float y, float w, float h)
	: CBackGround()
{
	Set(x, y, w, h);
}


void CBackGround::Render() {
	CRectangle::Render(mpTexture, 0.0f, 1280.0f, 1024.0f, 0.0f);
}