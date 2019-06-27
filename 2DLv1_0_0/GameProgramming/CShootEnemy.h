#ifndef CSHOOTENEMY_H
#define CSHOOTENEMY_H

#include "CCharacter.h"
#include "CTexture.h"


class CShootEnemy : public CCharacter {
	CTexture *mpTexture;
public:
	CShootEnemy();
	CShootEnemy(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
