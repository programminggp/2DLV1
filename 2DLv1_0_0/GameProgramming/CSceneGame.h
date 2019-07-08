#ifndef CSCENEGAME_H	//インクルードガード
#define CSCENEGAME_H	//インクルードガード

//CSceneクラスのインクルード
#include "CScene.h"

/*
クラスの定義
class クラス名 : public 親クラス名 {
public:
    命令
};
クラス名：CSceneGame
親クラス名：CScene
CSceneクラスを継承して
CSceneGameクラスを定義する
*/
class CSceneGame: public CScene {
public:
	/*
	デフォルトコンストラクタの宣言
	クラス名()
	クラスのインスタンスの生成時に呼ばれる
	*/
	CSceneGame();

	/*
	メソッドの宣言
	戻り値の型　メソッド名(引数);
	戻り値の型：void:戻り値なし
	メソッド名：Update
	引数：():引数なし
	インスタンスの更新処理を記述
	*/
	void Update();
	/*
	メソッドの宣言
	Render()
	インスタンスの描画処理を記述
	*/
	void Render();
};

#endif	//インクルードガード
