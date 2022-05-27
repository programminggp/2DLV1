#pragma once
#include "CCharacter.h"

class CBlock : public CCharacter
{
public:
	CBlock(float x, float y, float w, float h, CTexture* pt);
	void Update() {}
};