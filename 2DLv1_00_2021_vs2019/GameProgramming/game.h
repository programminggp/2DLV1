#ifndef GAME_H
#define GAME_H

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

}; //定義の終了;注意

#endif

