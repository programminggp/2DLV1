#pragma once
#include "CFont.h"
/*
* CUi
* ���[�U�[�C���^�t�F�[�X�N���X
*/
class CUi
{
public:
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
	int mEnemy;	//�G�̐�
	int mHp;
	int mTime;	//�o�ߎ���
	CFont mFont;
};
