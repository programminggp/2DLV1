#ifndef CSHOOTPLAYER_H
#define CSHOOTPLAYER_H

#include "CCharacter.h"
#include "CTexture.h"

class CShootPlayer : public CCharacter {
	CTexture *mpTexture;
public:
	CShootPlayer();
	CShootPlayer(float x, float y, float w, float h);
	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
