#pragma once
#include "CCharacter.h"

class CBullet : public CCharacter
{
public:
	CBullet();
	void Update();
	void Render();
	bool Collision(CRectangle* rect);
};