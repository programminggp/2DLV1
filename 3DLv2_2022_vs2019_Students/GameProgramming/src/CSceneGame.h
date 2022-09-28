#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"
#include "CXCharacter.h"
#include "CXPlayer.h"
#include "CXEnemy.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
private:
	CXEnemy mEnemy;
	//キャラクタのインスタンス
	CXPlayer mPlayer;
	CText mFont;

public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif