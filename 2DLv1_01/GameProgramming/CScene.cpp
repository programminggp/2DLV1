/*
ヘッダファイルのインクルード
#include "インクルードファイル名"
*/
#include "CScene.h"
//printf関数のインクルード
#include <stdio.h>
//gl関数のインクルード
#include "glut.h"

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
	/*
	四角形の描画
	*/
	/*
	描画指定の開始
	glBegin(mode)
	mode:GL_QUADS 四角形の描画
	*/
	glBegin(GL_QUADS);
	/*
	頂点座標の指定
	glVertex2f(x,y)
	x：X座標
	y：Y座標
	*/
	glVertex2f(-50.0f, 50.0f);
	glVertex2f(-50.0f, -50.0f);
	glVertex2f(50.0f, -50.0f);
	glVertex2f(50.0f, 50.0f);
	/*
	描画指定の終了
	glEnd()
	*/
	glEnd();
}
