#ifndef CENEMY_H
#define CENEMY_H

#include "CCharacter.h"
#include "CTexture.h"
#include "CEffect.h"

class CEnemy : public CCharacter {
public:
	CEffect mEffect;
	CTexture *mpTexture;
	int mVelocity;
	int mShot;

	CEnemy();
	CEnemy(float x, float y, float w, float h);

	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};


#endif
