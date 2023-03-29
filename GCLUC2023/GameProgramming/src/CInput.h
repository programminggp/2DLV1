#pragma once
#include <Windows.h>
#include "GLFW/glfw3.h"

class CInput
{
private:
	static GLFWwindow* spWindow;	//ウィンドウのポインタ

public:
	static void Window(GLFWwindow* pwindow);
	void GetMousePos(float* px, float* py);

	CInput();
	//bool Key(文字)
	//戻り値
	//true:文字のキーが押されている
	//false:文字のキーが押されていない
	bool Key(char key);
};