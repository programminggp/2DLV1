#ifndef CSHOOTENEMY_H
#define CSHOOTENEMY_H

#include "CCharacter.h"

class CShootEnemy : public CCharacter {
public:
	CTexture *mpTexture;
	CShootEnemy();
	CShootEnemy(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
