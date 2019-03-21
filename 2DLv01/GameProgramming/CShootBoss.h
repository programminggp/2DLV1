#ifndef CSHOOTBOSS_H
#define CSHOOTBOSS_H

#include "CCharacter.h"
#include "CEffect.h"

class CShootBoss : public CCharacter {
public:
	float mXdir;
	CEffect mEffect;
	CShootBoss();
	void Update();
	void Collision(CTask& r);
};


#endif
