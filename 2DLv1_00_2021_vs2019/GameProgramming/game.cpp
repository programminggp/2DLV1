/*
Lesson1
CGameクラスの定義とインスタンスの作成
課題
CRectクラスの定義とインスタンスの作成

*/

#include <stdio.h> //printf_s関数の取り込み

class CGame //CGameクラスの定義
{ //定義の開始
public: //全てからアクセス可能
	void Update(); //Updateメソッドの宣言
}; //定義の終了;注意

void CGame::Update() //Updateメソッドの処理の定義
{ //処理の開始
	printf_s("CGame::Update()\n"); //printf_s関数の呼び出し"文字列"を出力
	//\nは改行

} //処理の終了

CGame gGame; //CGameクラスのインスタンスの作成

/*
GameLoop関数の定義
ゲームのメインループ
繰り返し呼ばれる処理
*/
void GameLoop() //GameLoop関数の処理の定義
{ //処理の開始

	printf_s("GameLoop()"); //printf_s関数の呼び出し"文字列"を出力
	gGame.Update(); //Updateメソッドの呼び出し

	return; //returnすると、処理が終わります
} //処理の終了
