#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
class CApplication
{
private:
	CCharacter mRectangle;
	CTexture mTexture;
	CCharacter mCharacter;
public:
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};