#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
//22
#include "CPlayer.h"
//?
#include "CMap.h"
//
#include "CAirBase.h"
//
#include "CPoint.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//
	CAirBase *mpAirBase;
	//キャラクタの作成
//	CCharacter Character;
	CPlayer Player;
//	CMap mMap;//マップのインスタンス
	CPoint *mpEnemyPoint;

	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

	//2D描画スタート
	//Start2D(左座標, 右座標, 下座標, 上座標)
	void Start2D(float left, float right, float bottom, float top);
	//2D描画終了
	void End2D();
	//ミニマップ描画
	void RenderMiniMap();
};

#endif
