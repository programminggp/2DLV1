#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
#include "CInput.h"
#include "CShootPlayer.h"
#include "CTexture.h"

class CPlayer : public CCharacter {
public:
	static CPlayer* mpInstance;
	CTexture *mpTexture;
	CInput mInput;
	int mHit;
	int mShootInterval;

	CPlayer();
	CPlayer(float x, float y, float w, float h);

	void Update();
	void Render();
//	void Collision(CTask& r);
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
