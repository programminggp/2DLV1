#ifndef CBOSS_H
#define CBOSS_H

#include "CCharacter.h"

class CBoss : public CCharacter {
	static CTexture mTexture;
	int mVelocity;
public:

	CBoss();
	CBoss(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CCharacter* mc, CCharacter* yc);
};


#endif
