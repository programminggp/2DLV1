#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"

#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CFreeMonster.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//キャラクタのインスタンス
	CXPlayer mPlayer;
	//敵のインスタンス
	CXEnemy mEnemy;

	CXEnemy mDummy[3];

	//
	CFreeMonster mFMonster;

	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

};

#endif
