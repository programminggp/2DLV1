#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CBullet.h"
#include "CEnemy.h"
class CApplication
{
private:
	CCharacter mRectangle;
	CTexture mTexture;
	CEnemy mCharacter;
	CBullet mBullet;
public:
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};