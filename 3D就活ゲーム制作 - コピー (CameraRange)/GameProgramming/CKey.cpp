#include "CKey.h"

bool CKey::Push(char key) {
	/*
	GetKeyState�֐��͈����̃L�[��������Ă����Ԃ���
	�擪�r�b�g��1��16�r�b�g�̒l��Ԃ��܂��B
	������Ă��Ȃ��Ɛ擪�r�b�g��0�ł��B
	0x8000��1000000000000000��16�r�b�g�̒l
	�i16�r�b�g��2�i���j�ł��B
	&�͘_���ω��Z(AND)�ł��B
	*/
	return (GetKeyState(key) & 0x8000) == 0x8000;
}

bool CKey::Flg[256];

bool CKey::Once(char key) {
	//�L�[��������Ă��邩
	if ((GetKeyState(key) & 0x8000)) {
		//!���Z�q�F�ے�
		//������������
		if (!Flg[key]) {
			//�������ɂ���
			Flg[key] = true;
			//���߂ĉ����ꂽ�̂�true�Ԃ�
			return true;
		}
	}
	else {
		//������Ă��Ȃ��̂�false�ɂ���
		Flg[key] = false;
	}
	//������Ă��Ȃ����A������
	return false;
}
