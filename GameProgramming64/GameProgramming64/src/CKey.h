#ifndef CKEY_H
#define CKEY_H

//GetKeyState�֐��̃w�b�_�t�@�C��
#include <Windows.h>
/*
CKey�N���X
�L�[�{�[�h���͂��擾����
*/
class CKey {
public:
	static bool Flg[256];
	/*
	Push��static(�X�^�e�B�b�N)���\�b�h
	key�̒l�̃L�[��������Ă����true���A
	������Ă��Ȃ����false��߂�
	*/
	static bool Push(char key);
	static bool Once(char key);
};

#endif
