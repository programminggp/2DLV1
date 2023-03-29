#pragma once
#include "CCharacter.h"
#include "CCharacterManager.h"
class CHeart : public CRectangle
{
protected:
public:
	CHeart(float x, float y, float w, float h, CTexture* pt);
	int mLeft, mRight, mBottom, mTop;
	CTexture* mpTexture;
	void Update();
	void Render();
};