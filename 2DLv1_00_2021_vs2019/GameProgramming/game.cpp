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

	//�f�t�H���g�R���X�g���N�^�̐錾
	//�߂�l�̌^�F�L�q�Ȃ�
	//���\�b�h���F�N���X���Ɠ���
	//�����F�Ȃ�
	CGame(); //�f�t�H���g�R���X�g���N�^�̐錾

	//�f�X�g���N�^�̐錾
	//�߂�l�̌^�F�L�q�Ȃ�
	//���\�b�h���F�N���X���̑O��~
	//�����F�Ȃ�
	~CGame(); //�f�X�g���N�^�̐錾

	//�X�V�����̐錾
	//�߂�l�̌^�Fvoid�͖߂�l�Ȃ�
	//���\�b�h���FUpdate
	//�����F�Ȃ�
	void Update(); //Update���\�b�h�̐錾

}; //��`�̏I��;�K�v

//���\�b�h�Ƃ� �������W�߂������ł�
//���\�b�h�̒�`�ł́A���\�b�h�̏������쐬���܂�
//���\�b�h���̑O�ɃN���X����::��t���܂�

//�Q�[���N���X�̃f�t�H���g�R���X�g���N�^�̒�`
CGame::CGame()
{ //�����̊J�n
	printf("CGame::CGame\n"); //�R���\�[����ʂɏo�͂���
} //�����̏I��

//�Q�[���N���X�̃f�X�g���N�^�̒�`
CGame::~CGame()
{ //�����̊J�n
	printf("CGame::~CGame\n"); //�R���\�[����ʂɏo�͂���
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

//�Q�[���N���X�̃|�C���^�ϐ�
//�Q�[���N���X�̃C���X�^���X��������
//�|�C���^�ϐ����쐬����
CGame *gpGame; //�Q�[���N���X�̃|�C���^�ϐ�gpGame�̍쐬

//����������
//�v���O�������s�̍ŏ���1�x�������s����鏈��
void Init()
{
	//new���߂ŁA�Q�[���N���X�̃C���X�^���X���쐬���A
	//�ϐ�gpGame�֑������
	gpGame = new CGame(); //���̎��Q�[���N���X�̃R���X�g���N�^���Ă΂��
}

//�X�V����
//�v���O�����̎��s���ɌJ��Ԃ����s����鏈��
void Update()
{
	//������ꂽ�|�C���^�ϐ����g���A
	//�Q�[���N���X��Update���\�b�h���Ăяo��
	gpGame->Update(); //gpGame��Update���\�b�h�̌Ăяo��
}

//�I������
//�v���O�����̏I�����Ɉ�x�������s����鏈��
void Destroy()
{
	//delete���߂�gpGame�ɑ�����ꂽ
	//�Q�[���N���X�̃C���X�^���X���폜����
	delete gpGame; //���̎��Q�[���N���X�̃f�X�g���N�^���Ă΂��
	printf("Push Any Key");
	getchar(); //�L�[�{�[�h���͑҂�
}
