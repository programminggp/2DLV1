#ifndef CSHOOTPLAYER_H
#define CSHOOTPLAYER_H

#include "CCharacter.h"

class CShootPlayer : public CCharacter {
public:
	static CTexture mTexture;
	CShootPlayer();
	CShootPlayer(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
