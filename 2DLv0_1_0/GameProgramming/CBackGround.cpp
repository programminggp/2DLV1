#include "CBackGround.h"

CBackGround::CBackGround() {
	LoadTexture("BackGround.tga");
	mPriority = -1;
//	Enable();
	mTag = EBACKGROUND;
}

void CBackGround::Render() {
	CRectangle::Render();
}