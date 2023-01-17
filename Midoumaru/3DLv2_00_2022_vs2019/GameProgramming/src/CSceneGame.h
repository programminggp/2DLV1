#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"
#include"CXCharacter.h"
#include"CXPlayer.h"
#include"CXEnemy.h"
#include"CXMutant.h"
#include "CActionCamera.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {

	CText mFont;
	//敵のインスタンス
	CXEnemy mEnemy;
public:
	CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

private:
	CActionCamera mActionCamera;
	//キャラクタのインスタンス
	CXPlayer* mPlayer;
	CXMutant* mMutant;
	
	CModel Underground;
	
	//CXCharacter mCharacter;

};

#endif