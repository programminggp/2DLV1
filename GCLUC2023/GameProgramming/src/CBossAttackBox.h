#pragma once
#include "CCharacter.h"
#include "CTask.h"

class CBossAttackBox : public CCharacter
{
private:
public:
	//�R���X�g���N�^
	CBossAttackBox(float x, float y, float w, float h, CTexture* pt);
	//�f�X�g���N�^
	~CBossAttackBox();

	//�X�V����
	void Update();

};