#pragma once
#include "CFont.h"
/*
* CUi
* ���[�U�[�C���^�t�F�[�X�N���X
*/
class CUi
{
public:
	void PosY(float f);
	void RotX(float f);
	void RotY(float f);
	//2D�`��X�^�[�g
	//Start2D(�����W, �E���W, �����W, ����W)
	void Start2D(float left, float right, float bottom, float top);
	//2D�`��I��
	void End2D();

	//�Q�[���N���A�\��
	void Clear();
	//�Q�[���I�[�o�[�\��
	void Over();
	//�X�^�[�g�\��
	void Start();
	//Enemy(�G�̐�)
	void Enemy(int enemy);
	CUi();
	void Hp(int hp);
	//Time(����)
	void Time(int time);
	void Render();
private:
	float mPosY;	//Y���W
	float mRotX;	//X��]�l
	float mRotY;	//Y��]�l
	int mEnemy;	//�G�̐�
	int mHp;
	int mTime;	//�o�ߎ���
	CFont mFont;
};
