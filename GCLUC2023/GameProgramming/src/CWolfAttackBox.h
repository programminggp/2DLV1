#pragma once
#include "CCharacter.h"
#include "CTask.h"

class CWolfAttackBox : public CCharacter
{
private:
public:
	//�R���X�g���N�^
	CWolfAttackBox(float x, float y, float w, float h, CTexture* pt);
	//�f�X�g���N�^
	~CWolfAttackBox();

	//�X�V����
	void Update();

};