#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
#include "CInput.h"
#include "CShootPlayer.h"
#include "CTexture.h"

class CPlayer : public CCharacter {
public:
	static CPlayer* mpInstance;
	static CTexture mTexture;
	CInput mInput;
	int mHit;
	int mShootInterval;

	CPlayer();
	void Update();
	void Render();
	void Collision(CTask& r);
};

#endif
