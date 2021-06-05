#ifndef CKEY_H
#define CKEY_H
#include <Windows.h>

/*
CKeyクラス
キーボード入力を取得する
*/
class CKey {
public:
	//Pushはstatic(スタティック)メソッド
	//keyが押されていればtrue
	static bool Push(char key);
	//キーが押された瞬間だけtrueを返す
	static bool Once(char key);
	//
	static bool Twice(char key);
};

#endif

