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
	bool GetKey(char key);
	/*
	keyの値のキーが押されたフレームだけtrueを、
	それ以外はfalseを戻す
	*/
	bool GetKeyDown(char key);
};

#endif
