#ifndef CINPUT_H
#define CINPUT_H
#include <Windows.h>

class CInput {
public:
	/*
	�}�E�X�J�[�\���̍��W���擾����
	GetMousePosDisp(X���W�|�C���^, Y���W�|�C���^)
	�f�B�X�v���C�̍�������_(0,0)�Ƃ����A
	�}�E�X�J�[�\���̍��W���A�����ɐݒ肷��
	��ʉE������X���v���X
	��ʉ�������Y���v���X
	*/
	static void GetMousePosDisp(int* px, int* py)
	{
		POINT point;
		//WindowsAPI
		GetCursorPos(&point);
		*px = point.x;
		*py = point.y;
	}
	/*
	�}�E�X�J�[�\���̍��W��ݒ肷��
	SetCursorPosDisp(X���W,Y���W)
	�f�B�X�v���C�̍��オ���_(0,0)
	*/
	static void SetMousePosDisp(int x, int y)
	{
		//WindowsAPI
		SetCursorPos(x, y);
	}

};
#endif
