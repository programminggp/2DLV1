#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
#include "CInput.h"
#include "CFont.h"
#include "CCollision.h"

class CPlayer : public CCharacter {
public:
	static CPlayer* mpInstance;
	CInput mInput;
	CFont mFont;
	int mHit;
	int mShootInterval;

	CPlayer();
	void Update();
	void Render();
	void Collision(CTask& r);
};

#endif
