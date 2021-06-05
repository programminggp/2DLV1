#ifndef CSCENEGAME_H
#define CSCENEGAME_H

#include "CModelX.h"
#include "CCamera.h"
#include "CTask.h"
#include "CMap.h"

class CSceneGame {
public:
	//*1
	//マップ
	CMap mMap;
	//カメラクラスのインスタンス
	CCamera mCamera;
	//Xモデルのインスタンス
	CModelX mModel;
	//敵のモデル
	CModelX mModelKnight;

	~CSceneGame() {
		//タスクマネージャの削除
		CTaskManager::Get()->Destroy();
	}

	void Init();
	void Update();
	void Render();
};

#endif
