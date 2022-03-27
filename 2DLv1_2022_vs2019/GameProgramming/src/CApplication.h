#pragma once
#include "CRectangle.h"
#include "CTexture.h"
class CApplication
{
private:
	CRectangle mRectangle;
	CTexture mTexture;
public:
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};