#pragma once
#ifndef CINPUT_H
#define CINPUT_H
#include <Windows.h>
#include "GLFW/glfw3.h"

class CInput
{
	//ウィンドウポインタ
	static GLFWwindow* mpWindow;
public:
	/*
	初期化
	Init（ウィンドウポインタ）
	*/
	static void Init(GLFWwindow* w);
	static void Window(GLFWwindow* pwindow);
	/*
	GetMousePos(X座標ポインタ、Y座標ポインタ)
	ウィンドウの左上を原点とした、の座標を
	マウスカーソルの座標を、引数に設定する
	*/
	static void GetMousePos(int* px, int* py);
	void GetMousePos(float* px, float* py);

	CInput();
	//bool Key(文字)
	//戻り値
	//true:文字のキーが押されている
	//false:文字のキーが押されていない
	bool Key(char key);
private:
	static GLFWwindow* spWindow;	//ウィンドウのポインタ
};
#endif