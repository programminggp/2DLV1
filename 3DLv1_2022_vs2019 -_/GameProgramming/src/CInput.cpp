#include "CInput.h"
#include <stdio.h>

GLFWwindow* CInput::spWindow = nullptr;	//�E�B���h�E�̃|�C���^
GLFWwindow* CInput::mpWindow = nullptr;	//�E�B���h�E�̃|�C���^

void CInput::Init(GLFWwindow* w)
{
	mpWindow = w;
}

void CInput::Window(GLFWwindow* pwindow)
{
	spWindow = pwindow;
}

void CInput::GetMousePos(int* px, int* py)
{
	double xpos, ypos;
	glfwGetCursorPos(mpWindow, &xpos, &ypos);
	*px = xpos;
	*py = ypos;
	return;
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
	printf("���̓C���X�^���X�����܂�܂���\n");
}

bool CInput::Key(char key)
{
	return GetAsyncKeyState(key) < 0;
}
