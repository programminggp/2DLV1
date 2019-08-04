#ifndef CBOMB
#define CBOMB

#include "CCharacter.h"
#include "CTexture.h"

class CBomb : public CCharacter {
	CTexture *mpTexture;
	int mFrame;
public:

	CBomb();
	CBomb(float x, float y, float w, float h);

	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
