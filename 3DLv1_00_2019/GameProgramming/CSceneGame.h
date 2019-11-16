#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//22
#include "CPlayer.h"
//
#include "CBillBoard.h"
/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//キャラクタの作成
	CCharacter Character;
	CPlayer Player;
	//
	CBillBoard BillBoard;

	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
