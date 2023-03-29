#pragma once
#include "CCharacter.h"
#include "CCharacterManager.h"

class CBossHp : public CRectangle
{
protected:
public:
	CBossHp(float x, float y, float w, float h, CTexture* pt);
	int mLeft, mRight, mBottom, mTop;
	CTexture* mpTexture;
	void Render();
};
