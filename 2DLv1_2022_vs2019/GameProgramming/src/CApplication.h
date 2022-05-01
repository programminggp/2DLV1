#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFont.h"

class CApplication
{
private:
//	CCharacter mRectangle;
	CPlayer mPlayer;
	CTexture mTexture;
	CEnemy mEnemy;
	CBullet mBullet;
	CInput mInput;
	CFont mFont;
	CRectangle mMiss;
public:
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};