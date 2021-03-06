#include <stdio.h> //printf_s関数を取り込む

/*
class
クラスとは小さなプログラムの作成単位です
*/
//クラスの定義
//class クラス名
class CLesson1 //CLesson1クラスの定義
{ //クラス定義の開始
public: //全てからのアクセスを許可
	CLesson1(); //CLesson1クラスのデフォルトコンストラクタの宣言
}; //クラス定義の終了 ;が必要なので注意

/*
コンストラクタとは
クラスのインスタンス（実体）が作成される時に実行される処理です
*/
//デフォルトコンストラクタの定義
//クラス名::クラス名()
CLesson1::CLesson1() //CLesson1クラスのデフォルトコンストラクタの定義
{ //処理の開始
	//printf_s関数を使うと、文字列を出力できます
	printf_s("CLesson1()"); //"文字列"を画面に出力（表示）する
} //処理の終了

class CLesson2
{
public:
	CLesson2();
};

CLesson2::CLesson2()
{
	printf_s("CLesson2()");
}


CLesson1 Instance; //CLesson1クラスのインスタンス（実体）の作成
CLesson2 Lesson2;

/*
GameLoop関数の定義
ゲームのメインループ
繰り返し呼ばれる処理
*/
void GameLoop() //GameLoop関数の定義
{ //処理の開始
	//CLesson2 instance; //CLesson2クラスのインスタンスを作成します
	//定義の中で作成されたインスタンスは処理が終了すると削除されます	

	return; //returnすると、処理が終わります
} //処理の終了
