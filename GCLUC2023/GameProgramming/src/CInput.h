#pragma once
#include <Windows.h>
#include "GLFW/glfw3.h"

class CInput
{
private:
	static GLFWwindow* spWindow;	//�E�B���h�E�̃|�C���^

public:
	static void Window(GLFWwindow* pwindow);
	void GetMousePos(float* px, float* py);

	CInput();
	//bool Key(����)
	//�߂�l
	//true:�����̃L�[��������Ă���
	//false:�����̃L�[��������Ă��Ȃ�
	bool Key(char key);
};