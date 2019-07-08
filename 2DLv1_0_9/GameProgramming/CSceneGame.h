#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CPlayer.h"
#include "CBackGround.h"
#include "CBoss.h"
#include "CTexture.h"
#include "CEnemy.h"
#include "CCamera.h"

//クラスの定義
class CSceneGame: public CScene {
public:
	//カメラの作成
	CCamera mCamera;
	//変数の作成
	CBackGround mBackGround;
	CPlayer mPlayer;
	CEnemy mEnemy;
	CBoss mBoss;

	//コンストラクタ
	CSceneGame();

	//メソッド（プログラム）の宣言
	void Update();
	void Render();
};

#endif
