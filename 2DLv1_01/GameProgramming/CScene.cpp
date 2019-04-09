/*
ヘッダファイルのインクルード
#include "インクルードファイル名"
*/
#include "CScene.h"
//printf関数のインクルード
#include <stdio.h>

//一度だけ実行されるInitメソッドの定義
void CScene::Init() {
	/*
	printf(文字列);
	文字列をコンソール画面へ出力する
	*/
	printf("Init()");
}

//繰り返し実行されるUpdateメソッドの定義
void CScene::Update() {
	printf("Update()\n");
}
