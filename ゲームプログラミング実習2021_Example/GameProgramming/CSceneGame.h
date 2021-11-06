#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CCameraControl.h"
#include "CMap.h"
#include "CFelguard.h"
#include "CKnight.h"
#include "CMap2.h"
/*
ゲームのシーン
*/
class CSceneGame : public CScene {
//	CKnight mKnight;
//	CFelguard mFelguard;
	CCameraControl mCameraControl;
//	CMap mMap;
	CMap2 mMap;
public:
	//キャラクタのインスタンス
//	CXPlayer mPlayer;
	//敵のインスタンス
//	CXEnemy mEnemy;
	CSceneGame();
	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

};

#endif
