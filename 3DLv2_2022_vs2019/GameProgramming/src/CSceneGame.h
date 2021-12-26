#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//
#include "CText.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {

	CText mFont;

public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
