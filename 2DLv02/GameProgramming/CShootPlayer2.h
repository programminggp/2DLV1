#ifndef CSHOOTPLAYER2_H
#define CSHOOTPLAYER2_H

#include "CCharacter.h"

class CShootPlayer2 : public CCharacter {
public:
	CShootPlayer2();
	CShootPlayer2(float x, float y, float w, float h);
	void Update();
	void Collision(CTask& r);
};



#endif
