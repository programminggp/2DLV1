#pragma once
#include "CRectangle.h"
#include "CTexture.h"
class CApplication
{
private:
	CRectangle mRectangle;
	CTexture mTexture;
public:
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();
};