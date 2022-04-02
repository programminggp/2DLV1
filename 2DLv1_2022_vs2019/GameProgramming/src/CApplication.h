#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
class CApplication
{
private:
	CCharacter mRectangle;
	CTexture mTexture;
	CCharacter mCharacter;
public:
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};