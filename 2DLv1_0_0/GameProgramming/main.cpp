#include "CMain2D.h"
#include "CSceneGame.h"

/*
main関数
プログラムで最初に呼ばれる関数
*/
int main(void)
{
	//2D用メインプログラムのインスタンスmainを作成
	CMain2D main;
	//CSceneGameクラスのインスタンスを生成し、
	//メインプログラムのシーンを設定する
	main.SetScene(new CSceneGame());
}
