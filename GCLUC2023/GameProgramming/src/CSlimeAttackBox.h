#pragma once
#include "CCharacter.h"
#include "CTask.h"

class CSlimeAttackBox : public CCharacter
{
private:
public:
	//�R���X�g���N�^
	CSlimeAttackBox(float x, float y, float w, float h, CTexture* pt);
	//�f�X�g���N�^
	~CSlimeAttackBox();

	//�X�V����
	void Update();

};