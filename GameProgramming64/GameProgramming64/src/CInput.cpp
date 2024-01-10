#include "CInput.h"
#include <stdio.h>

GLFWwindow* CInput::spWindow = nullptr;	//ウィンドウのポインタ

void CInput::Window(GLFWwindow* pwindow)
{
	spWindow = pwindow;
}

void CInput::GetMousePos(float* px, float* py)
{
	double xpos, ypos;
	glfwGetCursorPos(spWindow, &xpos, &ypos);
	*px = (float)xpos;
	*py = (float)ypos;
	return;
}
// マウスカーソルの表示設定
void CInput::ShowCursor(bool isShow)
{
	glfwSetInputMode
	(
		spWindow,
		GLFW_CURSOR,
		isShow ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED
	);
}
CInput::CInput()
{
	printf("入力インスタンスが生まれました\n");
}

bool CInput::Key(char key)
{
	return GetAsyncKeyState(key) < 0;
}
