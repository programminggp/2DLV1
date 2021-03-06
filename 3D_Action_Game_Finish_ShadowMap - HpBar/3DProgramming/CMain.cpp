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

//最初に1回だけ行う処理
void CMain::init() {
	mpScene = new CSceneGame();
	mpScene->Init();
}

//繰り返し実行される処理
void CMain::update() {
	mpScene->Update();
}
