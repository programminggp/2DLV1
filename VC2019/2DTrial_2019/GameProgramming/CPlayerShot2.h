#ifndef CPlayerShot2_H
#define CPlayerShot2_H

#include "CCharacter.h"
#include "CTexture.h"

class CPlayerShot2 : public CCharacter {
	CTexture *mpTexture;
public:
	CPlayerShot2();
	void Update();
	void Collision(CCharacter* my, CCharacter* you);
	void Render();
};

#endif
