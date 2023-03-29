#pragma once
#include "CCharacter.h"
#include "CCharacterManager.h"

class CBackGround4 : public CCharacter
{
protected:
public:
	CBackGround4::CBackGround4(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt);
	void Update();
};