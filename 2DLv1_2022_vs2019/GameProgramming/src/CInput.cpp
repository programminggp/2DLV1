#include "CInput.h"
#include <stdio.h>

CInput::CInput()
{
	printf("���̓C���X�^���X�����܂�܂���\n");
}

bool CInput::Key(char key)
{
	return GetAsyncKeyState(key) < 0;
}
