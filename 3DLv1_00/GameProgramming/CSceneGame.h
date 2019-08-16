#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"

/*
ゲームのシーン
*/
//CSceneクラスを継承する
class CSceneGame : public CScene {
public:

	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

	//デストラクタの宣言
	~CSceneGame();
};

#endif
