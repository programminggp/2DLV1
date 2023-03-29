#pragma once
#include "CCharacter.h"
#include "CTexture.h"
#include "CInput.h"
#include "CBossAttackBox.h"
#include "CBossAttackBox2.h"

#define BOSSX 2.0f 
#define BOSSY 2.0f

#define BOSSXXR 20.0f 
#define BOSSXXL -20.0f 

#define BOSSYY 20.0f

class CBoss : public CCharacter
{
	friend CBossAttackBox;
	friend CBossAttackBox2;
protected:
public:
	EState State();	//��Ԃ��擾����
	bool Enabled(); //����
	static CBoss* Instance4();
	static int BEhp(); //�I�I�J�~��HP
	//�G�̐���ݒ�
	static void Num(int num);
	//�G�̐����擾
	static int Num();
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
	//CWolf(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CBoss(float x, float y, float w, float h, CTexture* pt);
	//�X�V����
	void Update();
	static CTexture mTexture8;
	static CTexture* Texture8();
private:
	CBossAttackBox* mpBossAttackBox;
	CBossAttackBox2* mpBossAttackBox2;
	static CBoss* spInstance4;
	static int sBEhp; //�{�X��HP
	static int sNum;	//�G�̐�
	int mBossEattack; //�U����������
	int mBossEattack2; //�U����������
	int mBossTime; //�U���̃{�X�p�̎���
	int mBossTime2; //�_���[�W�̃{�X�p�̎���
	int mBossTime3; //���S�̃{�X�p�̎���
	int mBossTime4; //��U���̃{�X�p�̎���
	int mBossInvincible; //���G�p�̃{�X�p�̎���
	int mFlg1;
	int mFlg2;
	int mFlg3;
	int mFlg4;
	int mFlg5;
	int mBoss; //��
	EState mState; //���
	bool mEnabled; //����
	float mBVx;	//X�����x
	float mBVy;	//Y�����x
	float mBLR;
	CInput mInput;
};