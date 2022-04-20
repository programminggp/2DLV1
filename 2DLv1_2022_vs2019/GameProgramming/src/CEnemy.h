#pragma once
#include "CCharacter.h"

class CEnemy : public CCharacter
{
public:
	void Update();
	bool Collision(CRectangle* rect);
};