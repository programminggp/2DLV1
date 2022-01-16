#include "CInput.h"
//GetKeyState�֐��̃w�b�_�t�@�C��
#include <Windows.h>

CInput::CInput()
{
	memset(mFlg, 0, sizeof(mFlg));
}

bool CInput::GetKey(char key) {
	/*
	GetAsyncKeyState �֐��͈����̃L�[��������Ă����Ԃ���
	�擪�r�b�g��1��16�r�b�g�̒l��Ԃ��܂��B
	������Ă��Ȃ��Ɛ擪�r�b�g��0�ł��B
	0x8000��1000000000000000��16�r�b�g�̒l
	�i16�r�b�g��2�i���j�ł��B
	&�͘_���ω��Z(AND)�ł��B
	*/
	return (GetAsyncKeyState(key) & 0x8000) == 0x8000;
}

bool CInput::GetKeyDown(char key) {
	//�L�[��������Ă��邩
	if ((GetAsyncKeyState(key) & 0x8000)) {
		//!���Z�q�F�ے�
		//������������
		if (!mFlg[key]) {
			//�������ɂ���
			mFlg[key] = true;
			//���߂ĉ����ꂽ�̂�true�Ԃ�
			return true;
		}
	}
	else {
		//������Ă��Ȃ��̂�false�ɂ���
		mFlg[key] = false;
	}
	//������Ă��Ȃ����A������
	return false;
}
