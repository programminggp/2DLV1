/*
Lesson1
CGame�N���X�̒�`�ƃC���X�^���X�̍쐬
�ۑ�
CRect�N���X�̒�`�ƃC���X�^���X�̍쐬
*/

#include <stdio.h> //printf�֐��̎�荞��
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
�v���O�����̖��߂��W�߂��A�N���X�ɍ쐬����鏈���ł��B
*/
void CGame::Render() //Render���\�b�h�̏����̒�`
{ //�����̊J�n
	printf("CGame::Render()\n"); //printf�֐����Ăяo��"������"���o��
						//\n�͉��s
} //�����̏I��

CGame gGame; //CGame�N���X�̃C���X�^���X�̍쐬

/*
GameLoop�֐��̒�`
�Q�[���̃��C�����[�v
�Q�[�����s���J��Ԃ��Ă΂�鏈��
*/
void GameLoop() //GameLoop�֐��̏����̒�`
{ //�����̊J�n

	printf("GameLoop()\n"); //printf�֐����Ăяo��"������"���o��

	gGame.Render(); //gGame��Render���\�b�h�̌Ăяo��

	return; //return����ƁA�������I���܂�
} //�����̏I��
