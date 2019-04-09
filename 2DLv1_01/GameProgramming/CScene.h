/*
インクルードガード
2重にインクルードさせないようにする仕組み
#ifndef
#define
　～　
#endif
*/
/*
#ifndef マクロ名
マクロが定義されていなければ#endifまで有効
マクロが定義されていれば#endifまで無効
*/
#ifndef CSCENE_H
/*
#define マクロ名
マクロを定義する
*/
#define CSCENE_H

/*
class クラス名 {
クラスの定義
};
クラスの宣言と定義
*/
class CScene {
/*
アクセス指定子
public:
　これ以降のメンバはだれでも使用できる
protected:
　これ以降のメンバは自分と子供が使用できる
private:
　これ以降のメンバは自分だけが使用できる
*/
public:
	/*
	メンバの宣言
	クラスに宣言した変数やメソッドを、
	クラスのメンバと呼ぶ
	*/
	/*
	メソッドの宣言
	メソッドの戻り値の型 メソッド名(引数)
	void 戻り値なしのメソッド
	メソッド名() 引数なしのメソッド
	*/
	//一度だけ実行されるInitメソッドの宣言
	void Init();
	//繰り返し実行されるUpdateメソッドの宣言
	void Update();
};

//#ifndefの終わり
#endif
