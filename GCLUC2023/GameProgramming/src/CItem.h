#pragma once
#include "CCharacter.h"

class CItem : public CCharacter
{
private:
	static int mIh;
public:
	//�R���X�g���N�^
	CItem(float x, float y, float w, float h, CTexture* pt);
	static int Ih();
	//�Փˏ���2
	void Collision();
	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);

	//�X�V����
	void Update();
};