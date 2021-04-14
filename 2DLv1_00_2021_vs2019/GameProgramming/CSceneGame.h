#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:

	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//次のシーンの取得
	CScene::EScene CSceneGame::GetNextScene(){
		return mScene;
	}
};

#endif
