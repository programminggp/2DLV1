#ifndef CBOSS_H
#define CBOSS_H

#include "CCharacter.h"
#include "CShootBoss.h"
#include "CFont.h"

class CBoss : public CCharacter {
public:
	int mVelocity;
	CShootBoss mShootLeft;
	CShootBoss mShootRight;
	CFont mFont;
	int mHit;
	CEffect mEffect;
	CBoss();
	void Update();
	void Render();
	void Collision(CTask& r);
};


#endif
