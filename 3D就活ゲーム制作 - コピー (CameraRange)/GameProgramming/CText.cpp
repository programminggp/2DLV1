#include "CText.h"

//static�̃e�N�X�`���̃C���X�^���X
CTexture CText::mFont;
CTexture CText::mFont2;
CTexture CText::mFont3;
/*
DrawChar
������`�悷��
ch:�����f�[�^ x:X���W y:Y���W w:�� h:���� fontnumber:�g���t�H���g�̔ԍ�
*/
void CText::DrawChar(char ch, int x, int y, int w, int h, int fontnumber) {
	if (fontnumber == 1){
		mFont.DrawImage(x - w, x + w, y - h, y + h, ch - ' ');
	}
	if (fontnumber == 2){
		mFont2.DrawImage(x - w, x + w, y - h, y + h, ch - ' ');
	}
	if (fontnumber == 3){
		mFont3.DrawImage(x - w, x + w, y - h, y + h, ch - ' ');
	}

	/*//�X�}�[�g��:mFont�͔z��
	for (int i = 0; i < 3; i++){
		if (fontnumber == i){
			mFont[i].DrawImage(x - w, x + w, y - h, y + h, ch - ' ');
		}
	}*/
	
}
// s:������f�[�^ x:�擪������X���W y:�擪������Y���W
void CText::DrawString(char *s, int x, int y, int w, int h, int font_number) {
	//1�������`�悵�܂�
	for (int i = 0; s[i] != '\0'; i++) {
		//������`�悷��
		DrawChar(s[i], x, y, w, h, font_number);
		//�E�ֈړ�
		x += w * 2;
	}
}
