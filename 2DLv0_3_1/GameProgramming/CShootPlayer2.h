#ifndef CSHOOTPLAYER2_H
#define CSHOOTPLAYER2_H

#include "CCharacter.h"
#include "CTexture.h"

class CShootPlayer2 : public CCharacter {
public:
	CTexture *mpTexture;
	CShootPlayer2();
	void Update();
	//	void Collision(CTask& r);
	void Collision(CCharacter* my, CCharacter* you);
	void Render();
};

#endif
