#include "CInput.h"
#include "windows.h"//WindowsAPIを使用する
/*
int CInput::Key(char key)
keyのキーが、押されていたら1を戻す
keyのキーが、押されていなければ0を戻す
key:キーの値
*/
int CInput::Key(char key) {
	//keyが押されていると0以外になる
	if ((GetKeyState(key) & 0x8000) != 0) {
		//押されているので1を戻す
		return 1;
	}
	//押されていないので0を戻す
	return 0;
}
