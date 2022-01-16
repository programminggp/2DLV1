#include "CInput.h"
//GetKeyState関数のヘッダファイル
#include <Windows.h>

CInput::CInput()
{
	memset(mFlg, 0, sizeof(mFlg));
}

bool CInput::GetKey(char key) {
	/*
	GetAsyncKeyState 関数は引数のキーが押されている状態だと
	先頭ビットが1の16ビットの値を返します。
	押されていないと先頭ビットは0です。
	0x8000は1000000000000000の16ビットの値
	（16ビットの2進数）です。
	&は論理積演算(AND)です。
	*/
	return (GetAsyncKeyState(key) & 0x8000) == 0x8000;
}

bool CInput::GetKeyDown(char key) {
	//キーが押されているか
	if ((GetAsyncKeyState(key) & 0x8000)) {
		//!演算子：否定
		//押し中か判定
		if (!mFlg[key]) {
			//押し中にする
			mFlg[key] = true;
			//初めて押されたのでtrue返す
			return true;
		}
	}
	else {
		//押されていないのでfalseにする
		mFlg[key] = false;
	}
	//押されていないか、押し中
	return false;
}
