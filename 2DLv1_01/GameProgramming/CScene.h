/*
インクルードガード
2重にインクルードさせないようにする仕組み
#ifndef マクロ名
#define マクロ名
　～　
#endif
*/

#ifndef CSCENE_H
/*
#ifndef CSCENE_H

マクロ定義のチェック
#ifndef マクロ名
マクロが定義されていなければ#endifまで有効
マクロが定義されていれば#endifまで無効
*/

#define CSCENE_H
/*
#define CSCENE_H

マクロを定義する
#define マクロ名
*/

//CSceneクラスの宣言と定義
class CScene {
/*
class CScene {

クラスの宣言と定義
class クラス名 {
	クラスの定義
};
*/

public:
/*
public:

アクセス指定子
public:
　これ以降のメンバはだれでも使用できる
protected:
　これ以降のメンバは自分と子供が使用できる
private:
　これ以降のメンバは自分だけが使用できる
*/

	/* メンバの宣言
	クラスで宣言した変数やメソッドを、
	クラスのメンバと呼ぶ
	*/

	//一度だけ実行されるInitメソッドの宣言
	void Init();
	/*
	void Init();

	メソッドの宣言
	メソッドの戻り値の型 メソッド名(引数)
	void 戻り値なしのメソッド
	メソッド名() 引数なしのメソッド
	*/

	//繰り返し実行されるUpdateメソッドの宣言
	void Update();
};

//#ifndefの終わり
#endif
