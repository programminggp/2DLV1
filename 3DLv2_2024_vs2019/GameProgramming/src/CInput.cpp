#include "CInput.h"
#include <stdio.h>

GLFWwindow* CInput::spWindow = nullptr;	//ウィンドウのポインタ

GLFWwindow* CInput::Window()
{
	return spWindow;
}

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

CInput::CInput()
{
	//printf("入力インスタンスが生まれました\n");
	memset(mPush, 0, sizeof(mPush));
}

bool CInput::Key(char key)
{
	return mPush[key] = GetAsyncKeyState(key) < 0; //true:Push 
}

bool CInput::KeyDown(char key)
{
	if (GetAsyncKeyState(key) < 0)
	{
		if (mPush[key])
		{
			return false;
		}
	}
	return mPush[key] = GetAsyncKeyState(key) < 0; //true:Push 
}
