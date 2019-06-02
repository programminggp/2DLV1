#include "CBackGround.h"

CBackGround::CBackGround() {
	mTexture.Load("BackGround.tga");
	mPriority = -1;
	mTag = EBACKGROUND;
}

void CBackGround::Render() {
	CRectangle::Render(&mTexture, 0.0f, 1280.0f, 1024.0f, 0.0f);
}