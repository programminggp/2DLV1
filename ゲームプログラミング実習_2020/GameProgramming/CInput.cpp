#include "CInput.h"
#include <Windows.h>
//�E�B���h�E�|�C���^
GLFWwindow* CInput::mpWindow = 0;
/*
������
Init(�E�B���h�E�|�C���^)
*/
void CInput::Init(GLFWwindow* w) {
	mpWindow = w;
}
/*
�}�E�X�J�[�\���̍��W���擾����
GetMousePos(X���W�|�C���^, Y���W�|�C���^)
�f�B�X�v���C�̍��オ���_(0,0)
��ʉE������X���v���X
��ʉ�������Y���v���X
*/
void CInput::GetMousePos(int *px, int *py) {
	POINT Point;
	//WindowsAPI
	GetCursorPos(&Point);
	*px = Point.x;
	*py = Point.y;
	return;
}
/*
�}�E�X�{�^���̏��
GetMouseButton(�{�^��)
�{�^��:
GLFW_MOUSE_BUTTON_LEFT:���{�^��
GLFW_MOUSE_BUTTON_RIGHT:�E�{�^��
return:
true�F������Ă���
false:������Ă��Ȃ�
*/
bool CInput::GetMouseButton(int button) {
	return GetAsyncKeyState(button);
//	int state = glfwGetMouseButton(mpWindow, button);
//	return state == GLFW_PRESS;
}
/*
�}�E�X�J�[�\���̍��W��ݒ肷��
SetCursorPos(X���W,Y���W)
*/
void CInput::SetMousePos(int x, int y) {
	//WindowsAPI
	SetCursorPos(x, y);
}

