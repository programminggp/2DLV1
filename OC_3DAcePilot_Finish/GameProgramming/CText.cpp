#include "CText.h"

//static�̃e�N�X�`���̃C���X�^���X
CTexture CText::mFont;
/*
DrawChar
������`�悷��
ch:�����f�[�^ x:X���W y:Y���W w:�� h:����
*/
void CText::DrawChar(char ch, int x, int y, int w, int h) {
	mFont.DrawImage(x - w, x + w, y - h, y + h, ch - ' ');
}
// s:������f�[�^ x:�擪������X���W y:�擪������Y���W
void CText::DrawString(char *s, int x, int y, int w, int h) {
	//1�������`�悵�܂�
	for (int i = 0; s[i] != '\0'; i++) {
		//������`�悷��
		DrawChar(s[i], x, y, w, h);
		//�E�ֈړ�
		x += w * 2;
	}
}
