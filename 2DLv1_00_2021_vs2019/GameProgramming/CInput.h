#ifndef CINPUT_H
#define CINPUT_H

/*
CInputクラス
入力を取得する
*/
class CInput {
	bool mFlg[256];
public:
	CInput();
	/*
	keyの値のキーが押されていればtrueを、
	押されていなければfalseを戻す
	*/
	bool Key(char key);
	/*
	keyの値のキーが押された瞬間だけtrueを、
	それ以外はfalseを戻す
	*/
	bool KeyOP(char key);
};

#endif
