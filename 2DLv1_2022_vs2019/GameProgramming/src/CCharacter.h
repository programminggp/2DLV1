#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include <stdio.h>
class CCharacter : public CRectangle
{
public:
	enum class EState	//���
	{
		EMOVE,	//�ړ�
		ESTOP	//��~
	};
protected:
	EState mState;
private:
	CTexture *mpTexture;
	int mLeft, mRight, mBottom, mTop;
public:
	virtual void Collision() {};
	virtual void Update() = 0;
	CCharacter();
	CTexture* Texture();
	void Texture(CTexture *pTexture, int left, int right, int bottom, int top);
	virtual void Render();
	void Move();
};