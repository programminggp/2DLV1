#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"

#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CFreeMonster.h"
#include "CFelguard.h"
#include "CFbxMutant.h"
#include "CBee.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	CFbxMutant mFbxMutant;
//	CModelX mIdle3;

	//キャラクタのインスタンス
	CXPlayer mPlayer;
	//敵のインスタンス
	CXEnemy mEnemy;

	CXEnemy mDummy[3];

	//
	CFreeMonster mFMonster;
	CFreeMonster mFMonster2;
	//
	CFelguard mFelguard;
	//
	CBee mBee;

	CSceneGame();

	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

};

#endif
