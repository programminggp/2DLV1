/*
Lesson1
CGame�N���X�̒�`�ƃC���X�^���X�̍쐬
�ۑ�
CRect�N���X�̒�`�ƃC���X�^���X�̍쐬

*/

#include <stdio.h> //printf_s�֐��̎�荞��

class CGame //CGame�N���X�̒�`
{ //��`�̊J�n
public: //�S�Ă���A�N�Z�X�\
	void Update(); //Update���\�b�h�̐錾
}; //��`�̏I��;����

void CGame::Update() //Update���\�b�h�̏����̒�`
{ //�����̊J�n
	printf_s("CGame::Update()\n"); //printf_s�֐��̌Ăяo��"������"���o��
	//\n�͉��s

} //�����̏I��

CGame gGame; //CGame�N���X�̃C���X�^���X�̍쐬

/*
GameLoop�֐��̒�`
�Q�[���̃��C�����[�v
�J��Ԃ��Ă΂�鏈��
*/
void GameLoop() //GameLoop�֐��̏����̒�`
{ //�����̊J�n

	printf_s("GameLoop()"); //printf_s�֐��̌Ăяo��"������"���o��
	gGame.Update(); //Update���\�b�h�̌Ăяo��

	return; //return����ƁA�������I���܂�
} //�����̏I��
