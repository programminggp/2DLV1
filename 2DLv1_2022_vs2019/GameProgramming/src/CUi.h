#pragma once
#include "CFont.h"
/*
* CUi
* ���[�U�[�C���^�t�F�[�X�N���X
*/
class CUi
{
public:
	CUi();
	void Hp(int hp);
	//Time(����)
	void Time(int time);
	void Render();
private:
	int mHp;
	int mTime;	//�o�ߎ���
	CFont mFont;
};
