#ifndef CTEXT_H
#define CTEXT_H

#include "CTexture.h"

/*
�����̕`��
*/
class CText {
public:
	//�e�N�X�`���̃C���X�^���X
	static CTexture mFont;
	static CTexture mFont2;
	static CTexture mFont3;
	//�����̕`��
	static void DrawChar(char ch, int x, int y, int w, int h, int fontnum = 1);
	//������̕`��
	//DrawString(������, ���X���W, ���Y���W, ������, ��������, �t�H���g�ԍ�(mFont��mFont2�Ȃ�))
	static void DrawString(char *s, int x, int y, int w, int h, int fontnum = 1);
};

#endif
