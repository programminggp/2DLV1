#pragma once
#include "CCharacter.h"
#include "CTask.h"

#define BOAX 1.5f 
#define BOAY 1.5f

class CBossAttackBox2 : public CCharacter
{
private:
	float mBAx;
	float mBAy;
public:
	//�R���X�g���N�^
	CBossAttackBox2(float x, float y, float w, float h, CTexture* pt);
	//�f�X�g���N�^
	~CBossAttackBox2();

	//�X�V����
	void Update();

};