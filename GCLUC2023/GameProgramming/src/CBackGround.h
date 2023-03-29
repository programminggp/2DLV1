#pragma once
#include "CCharacter.h"
#include "CCharacterManager.h"

class CBackGround : public CCharacter
{
protected:
public:
	CBackGround::CBackGround(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt);
	void Update();
};