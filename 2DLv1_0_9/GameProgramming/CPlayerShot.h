#ifndef CPLAYERSHOT_H
#define CPLAYERSHOT_H

#include "CCharacter.h"
#include "CTexture.h"

class CPlayerShot : public CCharacter {
public:
	static CPlayerShot mShot[5];
	CTexture *mpTexture;
	CPlayerShot();
	CPlayerShot(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
