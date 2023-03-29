#pragma once
#include <vector>
#include "CRectangle.h"
#include "CCharacter.h"
#include "CCharacterManager.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CInput.h"
#include "CFont.h"
#include "CGame.h"
#include "CSound.h"
#include "CBackGround.h"
#include "CHeart.h"
#include "CGage.h"
#include "CFont2.h"


class CApplication
{
private:
	enum class EState
	{
		ESTART,	//ゲーム開始
		EPLAY,	//ゲーム中
		ESTAGE1,
		ESTAGE2,
		EBOSS,
		ECLEAR,	//ゲームクリア
		EOVER,	//ゲームオーバー
	};

	CGame* mpGame;      //ゲームクラスのポインタ
	CPlayer* mpPlayer;  //プレイヤークラスのポインタ
	CEnemy* mpEnemy;    //敵クラスのポインタ
	EState mState;
	CInput mInput;
	CFont mFont;
	CFont2 mFont2;
	CBackGround* mpBackGround;

	static CTexture mTexture;  //プレイヤーテクスチャ
	static CTexture mTexture2; //背景テクスチャ
	static CTexture mTexture3; //スタート画面テクスチャ
	static CTexture mTexture4; //ゲームオーバー画面テクスチャ
	static CTexture mTexture5; //ゲームクリア画面テクスチャ
	static CTexture mTexture6;
	static CTexture mTexture7;
	static CTexture mTexture8;
	static CTexture mTexture9;
	static CTexture mTexture100; //ハート表示テクスチャ
	int mRb;
	int mMc;
	int mEs;
	int mNc;
	int mIg;
	//int mBd;
	static int mMm;
	static int mSi;
	static int mMu;
	static int mDi;
	static int mBd;
	static CTexture mTexture101; //スタミナ表示テクスチャ
	static CTexture mTexture102; //スタミナゲージ表示テクスチャ

public:
	static CTexture* Texture();
	static CTexture* Texture2();
	static CTexture* Texture3();
	static CTexture* Texture4();
	static CTexture* Texture5();
	static CTexture* Texture6();
	static CTexture* Texture7();
	static CTexture* Texture8();
	static CTexture* Texture9();
	static CTexture* Texture100();
	static CTexture* Texture101();
	static CTexture* Texture102();
	static int Mm();
	static int Si();
	static int Mu();
	static int Di();
	static int Bd();
	CApplication();
	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
};