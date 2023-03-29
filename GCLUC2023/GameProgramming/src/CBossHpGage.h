#pragma once
#include "CCharacter.h"
#include "CCharacterManager.h"

class CBossHpGage : public CRectangle
{
protected:
public:
	CBossHpGage(float x, float y, float w, float h, CTexture* pt);
	int mLeft, mRight, mBottom, mTop;
	CTexture* mpTexture;
	void Render();
};
