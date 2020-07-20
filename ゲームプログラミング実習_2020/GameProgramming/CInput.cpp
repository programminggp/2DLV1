#include "CInput.h"
#include <Windows.h>
//ウィンドウポインタ
GLFWwindow* CInput::mpWindow = 0;
/*
初期化
Init(ウィンドウポインタ)
*/
void CInput::Init(GLFWwindow* w) {
	mpWindow = w;
}
/*
マウスカーソルの座標を取得する
GetMousePos(X座標ポインタ, Y座標ポインタ)
ディスプレイの左上が原点(0,0)
画面右方向がX軸プラス
画面下方向がY軸プラス
*/
void CInput::GetMousePos(int *px, int *py) {
	POINT Point;
	//WindowsAPI
	GetCursorPos(&Point);
	*px = Point.x;
	*py = Point.y;
	return;
}
/*
マウスボタンの状態
GetMouseButton(ボタン)
ボタン:
GLFW_MOUSE_BUTTON_LEFT:左ボタン
GLFW_MOUSE_BUTTON_RIGHT:右ボタン
return:
true：押されている
false:押されていない
*/
bool CInput::GetMouseButton(int button) {
	return GetAsyncKeyState(button);
//	int state = glfwGetMouseButton(mpWindow, button);
//	return state == GLFW_PRESS;
}
/*
マウスカーソルの座標を設定する
SetCursorPos(X座標,Y座標)
*/
void CInput::SetMousePos(int x, int y) {
	//WindowsAPI
	SetCursorPos(x, y);
}

