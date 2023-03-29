#pragma once
#include "CFont.h"
#include "CFont2.h"
#include "CHeart.h"
#include "CStamina.h"
#include "CGage.h"
#include "CBossHp.h"
#include "CBossHpGage.h"
/*
* CUi
* ���[�U�[�C���^�t�F�[�X�N���X
*/
class CUi:public CRectangle
{
private:
	CBossHpGage mBossHpGage;
	CBossHp mBossHp;
	CStamina mStamina;
	CGage mGage;
	CHeart mHeart;
	int mBEhp;  //�{�X��HP
	int mEnemy;	//�G�̐�
	int mHp;    //�v���C���[��HP
	int mStaminagage; //�v���C���[�̃X�^�~�i
	int mTime;	//�o�ߎ���
	CFont mFont;
	CFont2 mFont2;

public:
	CTexture mTexture100;
	CTexture mTexture101;
	CTexture mTexture102;
	CTexture mTexture103;
	CTexture mTexture104;
	//�R���X�g���N�^
	CUi();
	//�f�X�g���N�^
	~CUi();

	//�Q�[���N���A�\��
	void Clear();
	//�Q�[���I�[�o�[�\��
	void Over();
	//�X�^�[�g�\��
	void Start();

	//Enemy(�G�̐�)
	void Enemy(int enemy);
	//Hp(�̗�)
	void Hp(int hp);
	//Stamina(�X�^�~�i)
	void Stamina(int stamina);
	//BossHp(�{�XHP)
	void BEhp(int behp);
	//Time(����)
	void Time(int time);
	//���U���g
	void DrawResult();
	void Render();
};
