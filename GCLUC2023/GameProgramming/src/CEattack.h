#pragma once
#include "CCharacter.h"

class CEattack : public CCharacter
{
private:
public:
	//�R���X�g���N�^
	CEattack(float x, float y, float w, float h, CTexture* pt);
	//�f�X�g���N�^
	~CEattack();

	//�X�V����
	void Update();

};