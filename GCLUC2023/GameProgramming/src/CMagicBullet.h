#pragma once
#include "CCharacter.h"

class CMagicBullet : public CCharacter
{
private:
public:
	//�R���X�g���N�^
	CMagicBullet(float x, float y, float w, float h, CTexture* pt);
	//�f�X�g���N�^
	~CMagicBullet();
 
	//�X�V����
	void Update();

};