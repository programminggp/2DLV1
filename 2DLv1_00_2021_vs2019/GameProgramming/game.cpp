/*
Lesson1
CGameクラスの定義とインスタンスの作成
課題
CRectクラスの定義とインスタンスの作成
*/

#include <stdio.h> //printf関数の取り込み
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
プログラムの命令を集めた、クラスに作成される処理です。
*/
void CGame::Render() //Renderメソッドの処理の定義
{ //処理の開始
	printf("CGame::Render()\n"); //printf関数を呼び出し"文字列"を出力
						//\nは改行
} //処理の終了

CGame gGame; //CGameクラスのインスタンスの作成

/*
GameLoop関数の定義
ゲームのメインループ
ゲーム実行中繰り返し呼ばれる処理
*/
void GameLoop() //GameLoop関数の処理の定義
{ //処理の開始

	printf("GameLoop()\n"); //printf関数を呼び出し"文字列"を出力

	gGame.Render(); //gGameのRenderメソッドの呼び出し

	return; //returnすると、処理が終わります
} //処理の終了
