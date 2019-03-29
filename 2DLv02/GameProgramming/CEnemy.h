#ifndef CENEMY_H
#define CENEMY_H

#include "CCharacter.h"

class CEnemy : public CCharacter {
public:
	int mVelocity;
	CEnemy();
	void Update();
	void Render();
	void Collision(CTask& r);
};


#endif
