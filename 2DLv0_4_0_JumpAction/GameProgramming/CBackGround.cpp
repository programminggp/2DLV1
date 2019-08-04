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
	r1.Set(x-w*2, y, w, h);
	r2.Set(x, y, w, h);
	r3.Set(x+w*2, y, w, h);
	r4.Set(x+w*4, y, w, h);
}


void CBackGround::Render() {
	r1.Render(mpTexture, 0.0f, 1000.0f, 750.0f, 0.0f);
	r2.Render(mpTexture, 1000.0f, 0.0f, 750.0f, 0.0f);
	r3.Render(mpTexture, 0.0f, 1000.0f, 750.0f, 0.0f);
	r4.Render(mpTexture, 1000.0f, 0.0f, 750.0f, 0.0f);
}