#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
#include "CInput.h"
#include "CShootPlayer.h"
#include "CFont.h"
#include "CCollision.h"

class CPlayer : public CCharacter {
public:
	static CPlayer* mpInstance;
	CInput mInput;
	CShootPlayer mShoot;
	CFont mFont;
	int mHit;
	CEffect mEffect;

	CPlayer();
	void Update();
	void Render();
	void Collision(CTask& r);
};

#endif
