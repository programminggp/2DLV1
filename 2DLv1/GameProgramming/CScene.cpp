#include "CScene.h"
#include "CRectangle.h"
#include <stdio.h>

//一度だけ実行されるメソッド
void CScene::Init() {
	printf("CMain::Init()\n");
}

//繰り返し実行されるメソッド
void CScene::Update() {
	printf("CMain::Update()\n");
	mRectangle.Render();
}