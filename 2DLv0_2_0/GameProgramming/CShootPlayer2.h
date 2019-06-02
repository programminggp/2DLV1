#ifndef CSHOOTPLAYER2_H
#define CSHOOTPLAYER2_H

#include "CCharacter.h"
#include "CTexture.h"

class CShootPlayer2 : public CCharacter {
public:
	static CTexture mTexture;
	CShootPlayer2();
	void Update();
	void Collision(CTask& r);
	void Render();
};

#endif
