#ifndef CENEMY_H
#define CENEMY_H

#include "CCharacter.h"

class CEnemy : public CCharacter {
public:
	static CTexture mTexture;
	int mVelocity;
	CEnemy();
	void Update();
	void Render();
	void Collision(CTask& r);
};


#endif
