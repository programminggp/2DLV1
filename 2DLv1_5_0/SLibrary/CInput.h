#ifndef CINPUT_H
#define CINPUT_H
#include "windows.h"
/*
CInputクラス
入力クラスの定義
*/
class CInput {
public:
	//keyが押されていれば1をおされていなければ0を返す
	int Key(char key);
};

#endif
