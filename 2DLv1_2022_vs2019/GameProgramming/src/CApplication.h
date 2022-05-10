#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFont.h"
#include "CMiss.h"
#include "CCharacterManager.h"
#include <vector>

class CApplication
{
private:
	enum class EState
	{
		ESTART,	//ゲーム開始
		EPLAY,	//ゲーム中
		ECLEAR,	//ゲームクリア
		EOVER,	//ゲームオーバー
	};
	EState mState;
//	CCharacter mRectangle;
	CPlayer mPlayer;
	CTexture mTexture;
	CEnemy mEnemy;
	CEnemy mEnemy2;
//	CBullet mBullet;
	CInput mInput;
	CFont mFont;
	CMiss mMiss;
	//CCharacterのポインタの可変長配列
	std::vector<CCharacter*> mCharacters;
	CCharacterManager mCharacterManager;
public:
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};