#pragma once
#include "CCharacter.h"
#include "CCharacterManager.h"

class CGage : public CRectangle
{
protected:
public:
	CGage(float x, float y, float w, float h, CTexture* pt);
	int mLeft, mRight, mBottom, mTop;
	CTexture* mpTexture;
	void Render();
};
