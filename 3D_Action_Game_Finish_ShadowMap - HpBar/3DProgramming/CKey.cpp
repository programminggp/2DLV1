#include "CKey.h"

#define TWICE_COUNT 10

/*
staticメソッドはクラスの外で定義
Push
keyの値のキーが押されていればtrueを、
押されていなければfalseを戻す
*/
bool CKey::Push(char key) {
	//GetKeyState関数は引数のキーが押されている状態だと
	//先頭ビットが1の16ビットの値を返します。
	//押されていないと先頭ビットは0です。
	//0x8000は1000000000000000の16ビットの値（16ビットの2進数）です。
	//&は論理積演算(AND)です。
	if (GetKeyState(key) & 0x8000) {
		return true;
	}
	return false;
}
/*
Once
キーボードのキーが押された瞬間だけtrueを返す。
押している間をfalseを返す。
*/
bool CKey::Once(char key) {
	static bool flg[256];
	//キーが押されているか
	if ((GetKeyState(key) & 0x8000)) {
		//!演算子：否定
		//押し中か判定
		if (!flg[key]) {
			flg[key] = true;
			//初めて押されたのでtrue返す
			return true;
		}
	}
	else {
		flg[key] = false;
	}
	return false;
}

bool CKey::Twice(char key) {
	static long flg[256];
	//キーが押されているか
	if ((GetKeyState(key) & 0x8000)) {
		//押し中か判定
		if (flg[key] <= TWICE_COUNT && flg[key] > 0) {
			//素早く2回と判定
			return true;
		}
		else {
			//1回目
			flg[key] = 0;
			return false;
		}
	}
	else {
		flg[key]++;
	}
	//押されていないか、押し中
	return false;
}
