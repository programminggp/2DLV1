#pragma once
#include "CCharacter.h"

class CEnemy : public CCharacter
{
private:
	static int mNum;	//�G�̐�

public:
	//�R���X�g���N�^
	CEnemy(float x, float y, float w, float h, CTexture* pt);
	//�f�X�g���N�^
	~CEnemy();

	//�G�̐���ݒ�
	static void Num(int num);
	//�G�̐����擾
	static int Num();

	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);

	//�X�V����
	void Update();
};