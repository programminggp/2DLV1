#include "Windows.h"
#include "CMain.h"

CMain::EState CMain::mState = CMain::INIT;

CMain::CMain()
: mpScene(0)
{ }

void CMain::loop() {
	switch (mState) {
	case INIT:
		init();
		mState = UPDATE;
		break;
	default:
		update();
	}
}

//�ŏ���1�񂾂��s������
void CMain::init() {
	mpScene = new CSceneGame();
	mpScene->Init();
}

//�J��Ԃ����s����鏈��
void CMain::update() {
	mpScene->Update();
}
