#include <stdio.h> //printf関数を取り込む
#include "glut.h" //グラフィックライブラリOpenGLを取り込む

/*
Lesson2
四角形の描画
課題
四角形の描画位置の変更
*/

//class クラスとはプログラムの作成単位です
//クラスの定義
//class クラス名

//ゲームクラスの定義
//クラス名；CGame
class CGame //CGameクラスの定義 
{ //定義の開始
public: //アクセス制限なし

	//メソッドの宣言
	//戻り値の型　メソッド名(引数)

	//初期化処理の宣言
	//戻り値の型：voidは戻り値なし
	//メソッド名：Init
	//引数：なし
	void Init(); //Initメソッドの宣言

	//更新処理の宣言
	//戻り値の型：voidは戻り値なし
	//メソッド名：Update
	//引数：なし
	void Update(); //Updateメソッドの宣言

}; //定義の終了;必要

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

//ゲームクラスのインスタンス作成
CGame gGame; //インスタンス変数gGameの作成

//初期化処理
//プログラム実行の最初に1度だけ実行される処理
void Init()
{
	gGame.Init(); //gGameのInitメソッドの呼び出し
}

//更新処理
//プログラムの実行中に繰り返し実行される処理
void Update()
{
	gGame.Update(); //gGameのUpdateメソッドの呼び出し
}
