#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//1
#include "CModel.h"
//4
#include "CPlayer.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//1
	CModel mSky;
	CModel mRock;
	CModel mRover;
	//10
	CModel mCube;
	//4
	CPlayer mPlayer;

	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

};

#endif
