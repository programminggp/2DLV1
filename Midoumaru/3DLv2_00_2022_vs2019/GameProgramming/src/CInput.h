#ifndef CINPUT_H
#define CINPUT_H
//WindowsAPI�p
#include <Windows.h>
//GLFW�p
#include "GLFW/glfw3.h"

class CInput {
public:
	//window�|�C���^�̐ݒ�
	static void Window(GLFWwindow* pwindow);
	/*
	�}�E�X�J�[�\���̍��W���擾����
	GetMousePosWin(X���W�|�C���^, Y���W�|�C���^)
	�E�B���h�E�̍�������_(0,0)�Ƃ����A
	�}�E�X�J�[�\���̍��W���A�����ɐݒ肷��
	��ʉE������X���v���X
	��ʉ�������Y���v���X
	*/
	static void GetMousePosWin(float* px, float* py);
	/*
	�}�E�X�J�[�\���̍��W��ݒ肷��
	SetMousePosWin(X���W,Y���W)
	�E�B���h�E�̍��オ���_(0,0)
	*/
	static void SetMousePosWin(float px, float py);
	/*
	�}�E�X�J�[�\���̍��W���擾����
	GetMousePosDisp(X���W�|�C���^, Y���W�|�C���^)
	�f�B�X�v���C�̍�������_(0,0)�Ƃ����A
	�}�E�X�J�[�\���̍��W���A�����ɐݒ肷��
	��ʉE������X���v���X
	��ʉ�������Y���v���X
	*/
	static void GetMousePosDisp(int* px, int* py);
	/*
	�}�E�X�J�[�\���̍��W��ݒ肷��
	SetMousePosDisp(X���W,Y���W)
	�f�B�X�v���C�̍��オ���_(0,0)
	*/
	static void SetMousePosDisp(int x, int y);

	//�}�E�X�z�C�[���ɕω�������ƌĂ΂��R�[���o�b�N�֐�
	static void MouseScrollCB(GLFWwindow* window, double x, double y);
	//�}�E�X�z�C�[����Ԃ̎擾
	//-1:���։�]�@0:��]�Ȃ��@1:��ɉ�]
	static int Wheel();
private:
	static GLFWwindow* spWindow;	//�E�B���h�E�̃|�C���^
	static int sWheel;	//�z�C�[���̏��
};
#endif

