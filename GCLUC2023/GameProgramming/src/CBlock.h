#pragma once
#include "CCharacter.h"

class CBlock: public CCharacter
{
private:
public:
	//�R���X�g���N�^
	CBlock(float x, float y, float w, float h, CTexture* pt);
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);

	//�X�V����
	void Update();
};