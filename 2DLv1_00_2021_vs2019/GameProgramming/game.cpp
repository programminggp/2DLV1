/*
Lesson2
�i�P�j�f�X�g���N�^�̍쐬
�i�Q�j\n
�ۑ�
�i�P�jCLesson2�N���X�̃f�X�g���N�^�̒ǉ�
�i�Q�jCLesson2�̃f�X�g���N�^�̊m�F
*/

#include <stdio.h> //printf_s�֐�����荞��

/*
class
�N���X�Ƃ͏����ȃv���O�����̍쐬�P�ʂł�
*/
//�N���X�̒�`
//class �N���X��
class CLesson1 //CLesson1�N���X�̒�`
{ //�N���X��`�̊J�n
public: //�S�Ă���̃A�N�Z�X������
	CLesson1(); //CLesson1�N���X�̃f�t�H���g�R���X�g���N�^�̐錾
	~CLesson1(); //CLesson1�N���X�̃f�X�g���N�^�̐錾
}; //�N���X��`�̏I�� ;���K�v�Ȃ̂Œ���

/*
�R���X�g���N�^�Ƃ�
�N���X�̃C���X�^���X�i���́j���쐬����鎞�Ɏ��s����鏈���ł�
*/
//�f�t�H���g�R���X�g���N�^�̒�`
//�N���X��::�N���X��()
CLesson1::CLesson1() //CLesson1�N���X�̃f�t�H���g�R���X�g���N�^�̒�`
{ //�����̊J�n
	//printf_s�֐����g���ƁA��������o�͂ł��܂�
	printf_s("CLesson1()"); //"������"����ʂɏo�́i�\���j����
} //�����̏I��

/*
�f�X�g���N�^�Ƃ�
�N���X�̃C���X�^���X�i���́j���폜����鎞�Ɏ��s����鏈���ł�
*/
//�f�X�g���N�^�̒�`
//�N���X��::~�N���X��()
CLesson1::~CLesson1()
{
	printf_s("~CLesson1()\n"); //\n�͉��s�����Ŏ��̍s�ւ����܂�
}

class CLesson2
{
public:
	CLesson2();
};

CLesson2::CLesson2()
{
	printf_s("CLesson2()");
}


CLesson1 Instance; //CLesson1�N���X�̃C���X�^���X�i���́j�̍쐬
CLesson2 Lesson2;

/*
GameLoop�֐��̒�`
�Q�[���̃��C�����[�v
�J��Ԃ��Ă΂�鏈��
*/
void GameLoop() //GameLoop�֐��̒�`
{ //�����̊J�n
	CLesson1 Instance; //CLesson1�N���X�̃C���X�^���X���쐬���܂�
	//{}�̒��ō쐬���ꂽ�C���X�^���X��}�̏������I������ƍ폜����܂�

	return; //return����ƁA�������I���܂�
} //�����̏I��
