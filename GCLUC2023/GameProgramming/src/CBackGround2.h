#pragma once
#include "CCharacter.h"
#include "CCharacterManager.h"

class CBackGround2 : public CCharacter
{
protected:
public:
	CBackGround2::CBackGround2(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt);
	void Update();
};