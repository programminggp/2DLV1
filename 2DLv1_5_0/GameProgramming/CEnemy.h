#ifndef CENEMY_H
#define CENEMY_H

#include "CCharacter.h"
#include "CTexture.h"

class CEnemy : public CCharacter {
	CTexture *mpTexture;
	bool mIsAlive;
	int mFrame;
	int mFx;
	int mFy;
public:
	int mFire;

	CEnemy();
	CEnemy(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};


#endif
