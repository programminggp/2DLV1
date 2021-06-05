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

//Å‰‚É1‰ñ‚¾‚¯s‚¤ˆ—
void CMain::init() {
	mpScene = new CSceneGame();
	mpScene->Init();
}

//ŒJ‚è•Ô‚µŽÀs‚³‚ê‚éˆ—
void CMain::update() {
	mpScene->Update();
}
