/*
Lesson2
�l�p�`�̕`��
�ۑ�
�l�p�`�̕`��ʒu�̕ύX
*/

#include "game.h" //�Q�[���N���X�̒�`����荞��
#include <stdio.h> //printf�֐�����荞��
#include "glut.h" //�O���t�B�b�N���C�u����OpenGL����荞��

//���\�b�h�Ƃ� �������W�߂������ł�
//���\�b�h�̒�`�ł́A���\�b�h�̏������쐬���܂�
//���\�b�h���̑O�ɃN���X����::��t���܂�

//�Q�[���N���X�̏��������\�b�h�̒�`
void CGame::Init()
{ //�����̊J�n
	printf("CGame::Init\n"); //�R���\�[����ʂɏo�͂���
} //�����̏I��

//�Q�[���N���X�̍X�V���\�b�h�̒�`
void CGame::Update()
{ //�����̊J�n

	//�l�p�`��`�悷��
	glBegin(GL_QUADS); //�`��J�n�i�l�p�`�j
	glVertex2f(0.0f, 0.0f); //���_���W�ݒ�iX���W,Y���W�j
	glVertex2f(100.0f, 0.0f); //���_�͔����v���ɐݒ�
	glVertex2f(100.0f, 100.0f);
	glVertex2f(0.0f, 100.0f);
	glEnd(); //�`��I��

} //�����̏I��
