#ifndef CTEXT_H
#define CTEXT_H

#include "CTexture.h"

/*
�����̕`��
*/
class CText {
	//�e�N�X�`���̃C���X�^���X
	CTexture mFont;
public:
	//�e�N�X�`���̃��[�h
	//LoadTexture(�e�N�X�`���t�@�C����, �s��, ��)
	void LoadTexture(const char *tga, int row, int col);
	//�����̕`��
	void DrawChar(char ch, int x, int y, int w, int h);
	//������`��
	void DrawString(const char *s, int x, int y, int w, int h);
};
#endif