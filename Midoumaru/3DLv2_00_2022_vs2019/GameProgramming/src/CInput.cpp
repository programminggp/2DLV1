#include "CInput.h"
GLFWwindow* CInput::spWindow = nullptr;//�E�B���h�E�̃|�C���^
int CInput::sWheel = 0;	//�z�C�[���̒l

void CInput::Window(GLFWwindow* pwindow)
{
	//�E�B���h�E�|�C���^�̕ۑ�
	spWindow = pwindow;
	//�R�[�X�o�b�N�֐��̓o�^
	glfwSetScrollCallback(spWindow, CInput::MouseScrollCB);
}

void CInput::GetMousePosWin(float* px, float* py)
{
	double xpos, ypos;
	//�}�E�X�J�[�\�����W�̎擾
	glfwGetCursorPos(spWindow, &xpos, &ypos);
	*px = (float)xpos;
	*py = (float)ypos;
	return;
}

void CInput::SetMousePosWin(float px, float py)
{
	//�}�E�X�J�[�\�����W�̐ݒ�
	glfwSetCursorPos(spWindow, px, py);
	return;
}
void CInput::GetMousePosDisp(int* px, int* py)
{
	POINT point;
	//WindowsAPI�@�}�E�X�J�[�\�����W�̎擾
	GetCursorPos(&point);
	*px = point.x;
	*py = point.y;
}

void CInput::SetMousePosDisp(int x, int y)
{
	//WindowsAPI�@�}�E�X�J�[�\�����W�̐ݒ�
	SetCursorPos(x, y);
}

//�}�E�X�z�C�[���ɕω�������ƌĂ΂��R�[���o�b�N�֐�
void CInput::MouseScrollCB(GLFWwindow* window, double x, double y)
{
	sWheel = (int)y;
}

int CInput::Wheel()
{
	int r = sWheel;
	sWheel = 0;
	return r;
}
