/*
Lesson2
四角形の描画
課題
四角形の描画位置の変更
*/

#include <stdio.h> //printf関数の取り込み
#include "glut.h" //グラフィックライブラリOpenGLの取り込み

/*
class
クラスとはプログラムの作成単位です
*/
//クラスの定義
//class クラス名
class CGame //CGameクラスの定義
{ //定義の開始
public: //全てからアクセス可能
	void Render(); //Renderメソッドの宣言
}; //定義の終了;注意

/*
メソッドとは
命令を集めた処理です。
*/
void CGame::Render() //Renderメソッドの定義
{ //処理の開始
	glBegin(GL_QUADS); //描画開始（四角形）
	glVertex2f(0.0f, 0.0f); //頂点座標設定（X座標,Y座標）
	glVertex2f(100.0f, 0.0f); //頂点は反時計回りに設定
	glVertex2f(100.0f, 100.0f);
	glVertex2f(0.0f, 100.0f);
	glEnd(); //描画終了
} //処理の終了

CGame gGame; //CGameクラスのインスタンスgGameの作成

/*
GameLoop関数の定義
ゲームのメインループ
ゲーム実行中繰り返し呼ばれる処理
*/
void GameLoop() //GameLoop関数の定義
{ //処理の開始

	gGame.Render(); //gGameのRenderメソッドの呼び出し

	return; //returnすると、処理が終わります
} //処理の終了
