#include "CScene.h"
/*
#include "CScene.h"

ヘッダファイルのインクルード
#include "インクルードファイル名"
C言語の標準関数のインクルード
#include <インクルードファイル名>
*/
//printf関数のインクルード
#include <stdio.h>
//gl関数のインクルード
#include "glut.h"

//一度だけ実行されるInitメソッドの定義
void CScene::Init() {
	//文字列を標準出力（画面）に出力する
	printf("Init()");
	/*
	printf("Init()");

	文字列定数を標準出力（画面）へ出力する
	printf(文字列定数);
	文字列定数："で囲まれた1文字以上の文字の値
	*/
}

//繰り返し実行されるUpdateメソッドの定義
void CScene::Update() {
	//文字列を標準出力（画面）に出力する
	printf("Update()\n");

	///*
	//四角形の描画
	//*/

	//glBegin(GL_QUADS);
	///*
	//glBegin(GL_QUADS);

	//描画指定の開始
	//glBegin(mode)
	//mode:GL_QUADS 四角形の描画
	//*/

	//glVertex2f(-50.0f, 50.0f);
	///*
	//glVertex2f(-50.0f, 50.0f);

	//頂点座標の指定
	//glVertex2f(x,y)
	//x：X座標
	//y：Y座標
	//*/
	///*
	//頂点は反時計回りに指定すること
	//*/

	//glVertex2f(-50.0f, -50.0f);
	//glVertex2f(50.0f, -50.0f);
	//glVertex2f(50.0f, 50.0f);

	//glEnd();
	///*
	//glEnd()

	//描画指定の終了
	//*/
}
