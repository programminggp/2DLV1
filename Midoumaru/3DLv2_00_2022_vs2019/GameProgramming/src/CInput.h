#ifndef CINPUT_H
#define CINPUT_H
//WindowsAPI用
#include <Windows.h>
//GLFW用
#include "GLFW/glfw3.h"

class CInput {
public:
	//windowポインタの設定
	static void Window(GLFWwindow* pwindow);
	/*
	マウスカーソルの座標を取得する
	GetMousePosWin(X座標ポインタ, Y座標ポインタ)
	ウィンドウの左上を原点(0,0)とした、
	マウスカーソルの座標を、引数に設定する
	画面右方向がX軸プラス
	画面下方向がY軸プラス
	*/
	static void GetMousePosWin(float* px, float* py);
	/*
	マウスカーソルの座標を設定する
	SetMousePosWin(X座標,Y座標)
	ウィンドウの左上が原点(0,0)
	*/
	static void SetMousePosWin(float px, float py);
	/*
	マウスカーソルの座標を取得する
	GetMousePosDisp(X座標ポインタ, Y座標ポインタ)
	ディスプレイの左上を原点(0,0)とした、
	マウスカーソルの座標を、引数に設定する
	画面右方向がX軸プラス
	画面下方向がY軸プラス
	*/
	static void GetMousePosDisp(int* px, int* py);
	/*
	マウスカーソルの座標を設定する
	SetMousePosDisp(X座標,Y座標)
	ディスプレイの左上が原点(0,0)
	*/
	static void SetMousePosDisp(int x, int y);

	//マウスホイールに変化があると呼ばれるコールバック関数
	static void MouseScrollCB(GLFWwindow* window, double x, double y);
	//マウスホイール状態の取得
	//-1:下へ回転　0:回転なし　1:上に回転
	static int Wheel();
private:
	static GLFWwindow* spWindow;	//ウィンドウのポインタ
	static int sWheel;	//ホイールの状態
};
#endif

