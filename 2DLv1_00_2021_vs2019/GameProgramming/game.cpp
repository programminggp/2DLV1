#include <stdio.h> //printf�֐�����荞��
#include "glut.h" //�O���t�B�b�N���C�u����OpenGL����荞��

/*
Lesson2
�l�p�`�̕`��
�ۑ�
�l�p�`�̕`��ʒu�̕ύX
*/

//class �N���X�Ƃ̓v���O�����̍쐬�P�ʂł�
//�N���X�̒�`
//class �N���X��

//�Q�[���N���X�̒�`
//�N���X���GCGame
class CGame //CGame�N���X�̒�` 
{ //��`�̊J�n
public: //�A�N�Z�X�����Ȃ�

	//���\�b�h�̐錾
	//�߂�l�̌^�@���\�b�h��(����)

	//�����������̐錾
	//�߂�l�̌^�Fvoid�͖߂�l�Ȃ�
	//���\�b�h���FInit
	//�����F�Ȃ�
	void Init(); //Init���\�b�h�̐錾

	//�X�V�����̐錾
	//�߂�l�̌^�Fvoid�͖߂�l�Ȃ�
	//���\�b�h���FUpdate
	//�����F�Ȃ�
	void Update(); //Update���\�b�h�̐錾

}; //��`�̏I��;�K�v

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

//�Q�[���N���X�̃C���X�^���X�쐬
CGame gGame; //�C���X�^���X�ϐ�gGame�̍쐬

//����������
//�v���O�������s�̍ŏ���1�x�������s����鏈��
void Init()
{
	gGame.Init(); //gGame��Init���\�b�h�̌Ăяo��
}

//�X�V����
//�v���O�����̎��s���ɌJ��Ԃ����s����鏈��
void Update()
{
	gGame.Update(); //gGame��Update���\�b�h�̌Ăяo��
}
