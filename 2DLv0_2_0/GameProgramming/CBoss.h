#ifndef CBOSS_H
#define CBOSS_H

#include "CCharacter.h"
#include "CShootBoss.h"

class CBoss : public CCharacter {
	static CTexture mTexture;
public:
	int mVelocity;
	CShootBoss mShootLeft;
	CShootBoss mShootRight;
	int mHit;

	CBoss();
	CBoss(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CTask& r);
};


#endif
