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
	//�����̕`��
	static void DrawChar(char ch, int x, int y, int w, int h);
	//������̕`��
	static void DrawString(char *s, int x, int y, int w, int h);
};

#endif
