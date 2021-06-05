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
	//�ŏ���1�񂾂��s������
	void init();
	//�J��Ԃ����s����鏈��
	void update();

};


