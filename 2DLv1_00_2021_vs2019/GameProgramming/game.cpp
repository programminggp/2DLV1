/*
Lesson2
�l�p�`�̕`��
�ۑ�
�l�p�`�̕`��ʒu�̕ύX
*/

#include <stdio.h> //printf�֐��̎�荞��
#include "glut.h" //�O���t�B�b�N���C�u����OpenGL�̎�荞��

/*
class
�N���X�Ƃ̓v���O�����̍쐬�P�ʂł�
*/
//�N���X�̒�`
//class �N���X��
class CGame //CGame�N���X�̒�`
{ //��`�̊J�n
public: //�S�Ă���A�N�Z�X�\
	void Render(); //Render���\�b�h�̐錾
}; //��`�̏I��;����

/*
���\�b�h�Ƃ�
���߂��W�߂������ł��B
*/
void CGame::Render() //Render���\�b�h�̒�`
{ //�����̊J�n
	glBegin(GL_QUADS); //�`��J�n�i�l�p�`�j
	glVertex2f(0.0f, 0.0f); //���_���W�ݒ�iX���W,Y���W�j
	glVertex2f(100.0f, 0.0f); //���_�͔����v���ɐݒ�
	glVertex2f(100.0f, 100.0f);
	glVertex2f(0.0f, 100.0f);
	glEnd(); //�`��I��
} //�����̏I��

CGame gGame; //CGame�N���X�̃C���X�^���XgGame�̍쐬

/*
GameLoop�֐��̒�`
�Q�[���̃��C�����[�v
�Q�[�����s���J��Ԃ��Ă΂�鏈��
*/
void GameLoop() //GameLoop�֐��̒�`
{ //�����̊J�n

	gGame.Render(); //gGame��Render���\�b�h�̌Ăяo��

	return; //return����ƁA�������I���܂�
} //�����̏I��
