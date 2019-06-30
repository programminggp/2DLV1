#ifndef CENEMY_H
#define CENEMY_H

#include "CCharacter.h"
#include "CTexture.h"

class CEnemy : public CCharacter {
public:
	CTexture *mpTexture;
	int mVelocity;
	int mFire;

	CEnemy();
	CEnemy(float x, float y, float w, float h);
	void Update();
	void Render();
	//	void Collision(CTask& r);
	void Collision(CCharacter* my, CCharacter* you);
};


#endif
