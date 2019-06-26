#ifndef CBOSS_H
#define CBOSS_H

#include "CCharacter.h"

class CBoss : public CCharacter {
	int mVelocity;
public:
	CTexture* mpTexture;
	float mX, mY, mW, mH;

	CBoss();
	CBoss(float x, float y, float w, float h);
	void Set(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CCharacter* mc, CCharacter* yc);
};


#endif
