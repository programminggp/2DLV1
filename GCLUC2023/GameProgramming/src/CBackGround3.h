#pragma once
#include "CCharacter.h"
#include "CCharacterManager.h"

class CBackGround3 : public CCharacter
{
protected:
public:
	CBackGround3::CBackGround3(float x, float y, float w, float h, float l, float r, float b, float t, CTexture* pt);
	void Update();
};
