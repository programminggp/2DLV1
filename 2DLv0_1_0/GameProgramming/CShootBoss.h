#ifndef CSHOOTBOSS_H
#define CSHOOTBOSS_H

#include "CCharacter.h"
#include "CEffect.h"

class CShootBoss : public CCharacter {
public:
	static CTexture mTexture;
	float mXdir;
	CShootBoss();
	void Update();
	void Collision(CTask& r);
	void Render();
};


#endif
