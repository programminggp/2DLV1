#pragma once
#include "CCharacter.h"

class CEnemy : public CCharacter
{
public:
	CEnemy();
	void Update();
	bool Collision(CRectangle* rect);
	bool Collision(CCharacter* m, CCharacter* o);
};