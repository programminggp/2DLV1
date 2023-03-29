#pragma once
#include "CCharacter.h"
#include "CCharacterManager.h"

class CStamina : public CRectangle
{
protected:
public:
	CStamina(float x, float y, float w, float h, CTexture* pt);
	int mLeft, mRight, mBottom, mTop;
	CTexture* mpTexture;
	void Update();
	void Render();
};