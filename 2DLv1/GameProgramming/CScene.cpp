#include "CScene.h"
#include "CRectangle.h"
#include <stdio.h>

//一度だけ実行されるメソッド
void CScene::Init() {
	printf("CMain::Init()\n");
	mRectangle.mPx = 370;
	mRectangle.mPy = 270;
	mRectangle.mSx = 30;
	mRectangle.mSy = 30;
}

//繰り返し実行されるメソッド
void CScene::Update() {
	printf("CMain::Update()\n");
	mRectangle.Render();
}