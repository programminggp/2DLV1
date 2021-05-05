/*
Lesson2
四角形の描画
課題
四角形の描画位置の変更
*/

#include "game.h" //ゲームクラスの定義を取り込む
#include <stdio.h> //printf関数を取り込む
#include "glut.h" //グラフィックライブラリOpenGLを取り込む

//メソッドとは 処理を集めた処理です
//メソッドの定義では、メソッドの処理を作成します
//メソッド名の前にクラス名と::を付けます

//ゲームクラスの初期化メソッドの定義
void CGame::Init()
{ //処理の開始
	printf("CGame::Init\n"); //コンソール画面に出力する
} //処理の終了

//ゲームクラスの更新メソッドの定義
void CGame::Update()
{ //処理の開始

	//四角形を描画する
	glBegin(GL_QUADS); //描画開始（四角形）
	glVertex2f(0.0f, 0.0f); //頂点座標設定（X座標,Y座標）
	glVertex2f(100.0f, 0.0f); //頂点は反時計回りに設定
	glVertex2f(100.0f, 100.0f);
	glVertex2f(0.0f, 100.0f);
	glEnd(); //描画終了

} //処理の終了
