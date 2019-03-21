#include "CBackGround.h"

CBackGround::CBackGround() {
	LoadTexture("BackGround.tga");
	Enable();
	mTag = EBACKGROUND;
}

