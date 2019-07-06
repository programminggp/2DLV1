#ifndef CBOSS_H
#define CBOSS_H

#include "CCharacter.h"
#include "CTexture.h"
#include "CEffect.h"

class CBoss : public CCharacter {
	int mVelocity;
public:
	CEffect mEffect;
	CTexture* mpTexture;

	CBoss();
	CBoss(float x, float y, float w, float h);

	void Update();
	void Render();
	void Collision(CCharacter* mc, CCharacter* yc);
};


#endif
