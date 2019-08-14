#ifndef CEXPLOSION
#define CEXPLOSION

#include "CCharacter.h"
#include "CTexture.h"

class CExplosion : public CCharacter {
	CTexture *mpTexture;
	int mFrame;
	float mU, mV;
	enum ETagExp {
		ECENTER,
		EUP,
		ELEFT,
		ERIGHT,
		EDOWN
	};
	ETagExp mTagExp;
	int mCount;
public:

	CExplosion();
	CExplosion(float x, float y, float w, float h, int count);
	CExplosion(float x, float y, float w, float h, int count, ETagExp tag);

	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
