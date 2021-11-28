#ifndef CSCENETEST_H
#define CSCENETEST_H
#include "CScene.h"
#include "CText.h"
#include "CKey.h"
#include <Windows.h>
#include "CSound.h"
#include "CModel.h"

class CSceneTest : public CScene {
private:
	CModel mCource05Road;
	CVector e, c, u;
public:
	CSceneTest()
		: e(0.0f, 20000.0f, 0.0f), c(0.0f, 0.0f, 0.0f), u(0.0f, 0.0f, 1.0f)
	{}

	~CSceneTest();

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//次のシーンの取得
	EScene GetNextScene();	
};

#endif