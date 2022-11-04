#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"
#include "CXCharacter.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CActionCamera.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
private:
	CActionCamera mActionCamera;
	CXEnemy mEnemy;
	//キャラクタのインスタンス
	CXPlayer mPlayer;
	CText mFont;

public:
	CSceneGame()
		: mActionCamera(5.0f, -15.0f, 180.0f)
	{}
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif