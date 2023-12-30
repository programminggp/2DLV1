#pragma once
#ifndef CINPUT_H
#define CINPUT_H
#include <Windows.h>
#include "GLFW/glfw3.h"

class CInput
{
	//�E�B���h�E�|�C���^
	static GLFWwindow* mpWindow;
public:
	/*
	������
	Init�i�E�B���h�E�|�C���^�j
	*/
	static void Init(GLFWwindow* w);
	static void Window(GLFWwindow* pwindow);
	/*
	GetMousePos(X���W�|�C���^�AY���W�|�C���^)
	�E�B���h�E�̍�������_�Ƃ����A�̍��W��
	�}�E�X�J�[�\���̍��W���A�����ɐݒ肷��
	*/
	static void GetMousePos(int* px, int* py);
	void GetMousePos(float* px, float* py);

	CInput();
	//bool Key(����)
	//�߂�l
	//true:�����̃L�[��������Ă���
	//false:�����̃L�[��������Ă��Ȃ�
	bool Key(char key);
private:
	static GLFWwindow* spWindow;	//�E�B���h�E�̃|�C���^
};
#endif