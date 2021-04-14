#ifndef CINPUT_H
#define CINPUT_H

/*
CInputクラス
入力を取得する
*/
class CInput {
public:
	static bool Flg[256];
	/*
	Keyはstatic(スタティック)メソッド
	keyの値のキーが押されていればtrueを、
	押されていなければfalseを戻す
	*/
	static bool Key(char key);
	static bool KeyOP(char key);
};

#endif
