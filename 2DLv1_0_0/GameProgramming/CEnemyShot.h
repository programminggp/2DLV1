#ifndef CENEMYSHOT_H
#define CENEMYSHOT_H

#include "CCharacter.h"
#include "CTexture.h"


class CEnemyShot : public CCharacter {
public:
	static CEnemyShot mShot[5];
	CTexture *mpTexture;
	CEnemyShot();
	CEnemyShot(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
