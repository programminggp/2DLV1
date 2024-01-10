#include "CInput.h"
#include <stdio.h>

GLFWwindow* CInput::spWindow = nullptr;	//�E�B���h�E�̃|�C���^

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
// �}�E�X�J�[�\���̕\���ݒ�
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
	printf("���̓C���X�^���X�����܂�܂���\n");
}

bool CInput::Key(char key)
{
	return GetAsyncKeyState(key) < 0;
}
