#pragma once
#include <Windows.h>
#include "GLFW/glfw3.h"

class CInput
{
public:
	static GLFWwindow* Window();
	static void Window(GLFWwindow* pwindow);
	void GetMousePos(float* px, float* py);

	CInput();
	//bool Key(文字)
	//戻り値
	//true:文字のキーが押されている
	//false:文字のキーが押されていない
	bool Key(char key);
	//bool KeyDown(文字)
	//戻り値
	//true:文字のキーが押された時
	//false:文字のキーが押された時以外
	bool KeyDown(char key);
private:
	static GLFWwindow* spWindow;	//ウィンドウのポインタ
	bool mPush[256];
};