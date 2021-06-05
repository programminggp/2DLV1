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
	//Å‰‚É1‰ñ‚¾‚¯s‚¤ˆ—
	void init();
	//ŒJ‚è•Ô‚µÀs‚³‚ê‚éˆ—
	void update();

};


