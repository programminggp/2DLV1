#ifndef CKEY_H
#define CKEY_H
#include <Windows.h>

/*
CKey�N���X
�L�[�{�[�h���͂��擾����
*/
class CKey {
public:
	//Push��static(�X�^�e�B�b�N)���\�b�h
	//key��������Ă����true
	static bool Push(char key);
	//�L�[�������ꂽ�u�Ԃ���true��Ԃ�
	static bool Once(char key);
	//
	static bool Twice(char key);
};

#endif

