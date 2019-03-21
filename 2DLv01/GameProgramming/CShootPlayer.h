#ifndef CSHOOTPLAYER_H
#define CSHOOTPLAYER_H

#include "CCharacter.h"
#include "CEffect.h"

class CShootPlayer : public CCharacter {
public:
	CEffect mEffect;
	CShootPlayer();
	void Update();
	void Collision(CTask& r);
};

#endif
