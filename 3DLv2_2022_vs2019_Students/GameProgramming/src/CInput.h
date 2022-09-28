#ifndef CINPUT_H
#define CINPUT_H
#include <Windows.h>

class CInput {
public:
	/*
	マウスカーソルの座標を取得する
	GetMousePosDisp(X座標ポインタ, Y座標ポインタ)
	ディスプレイの左上を原点(0,0)とした、
	マウスカーソルの座標を、引数に設定する
	画面右方向がX軸プラス
	画面下方向がY軸プラス
	*/
	static void GetMousePosDisp(int* px, int* py)
	{
		POINT point;
		//WindowsAPI
		GetCursorPos(&point);
		*px = point.x;
		*py = point.y;
	}
	/*
	マウスカーソルの座標を設定する
	SetCursorPosDisp(X座標,Y座標)
	ディスプレイの左上が原点(0,0)
	*/
	static void SetMousePosDisp(int x, int y)
	{
		//WindowsAPI
		SetCursorPos(x, y);
	}

};
#endif
