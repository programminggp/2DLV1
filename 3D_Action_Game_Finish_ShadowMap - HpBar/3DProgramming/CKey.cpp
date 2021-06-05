#include "CKey.h"

#define TWICE_COUNT 10

/*
static���\�b�h�̓N���X�̊O�Œ�`
Push
key�̒l�̃L�[��������Ă����true���A
������Ă��Ȃ����false��߂�
*/
bool CKey::Push(char key) {
	//GetKeyState�֐��͈����̃L�[��������Ă����Ԃ���
	//�擪�r�b�g��1��16�r�b�g�̒l��Ԃ��܂��B
	//������Ă��Ȃ��Ɛ擪�r�b�g��0�ł��B
	//0x8000��1000000000000000��16�r�b�g�̒l�i16�r�b�g��2�i���j�ł��B
	//&�͘_���ω��Z(AND)�ł��B
	if (GetKeyState(key) & 0x8000) {
		return true;
	}
	return false;
}
/*
Once
�L�[�{�[�h�̃L�[�������ꂽ�u�Ԃ���true��Ԃ��B
�����Ă���Ԃ�false��Ԃ��B
*/
bool CKey::Once(char key) {
	static bool flg[256];
	//�L�[��������Ă��邩
	if ((GetKeyState(key) & 0x8000)) {
		//!���Z�q�F�ے�
		//������������
		if (!flg[key]) {
			flg[key] = true;
			//���߂ĉ����ꂽ�̂�true�Ԃ�
			return true;
		}
	}
	else {
		flg[key] = false;
	}
	return false;
}

bool CKey::Twice(char key) {
	static long flg[256];
	//�L�[��������Ă��邩
	if ((GetKeyState(key) & 0x8000)) {
		//������������
		if (flg[key] <= TWICE_COUNT && flg[key] > 0) {
			//�f����2��Ɣ���
			return true;
		}
		else {
			//1���
			flg[key] = 0;
			return false;
		}
	}
	else {
		flg[key]++;
	}
	//������Ă��Ȃ����A������
	return false;
}
