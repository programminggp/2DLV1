#pragma once

#include "CSceneGame.h"

class CMain {
public:
	CSceneGame *mpScene;
	enum EState {
		INIT,
		UPDATE,
	};
	static EState mState;

	CMain();
	~CMain() {
		if (mpScene)
			delete mpScene;
		mpScene = 0;
	}

	void loop();
	//最初に1回だけ行う処理
	void init();
	//繰り返し実行される処理
	void update();

};


