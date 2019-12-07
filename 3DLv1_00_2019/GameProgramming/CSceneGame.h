#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//22
#include "CPlayer.h"
//?
#include "CMap.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//キャラクタの作成
//	CCharacter Character;
	CPlayer Player;
	CMap mMap;//マップのインスタンス

	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif
