#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
#include "CInput.h"
#include "CShootPlayer.h"
#include "CTexture.h"
#include "CShootPlayer.h"

class CPlayer : public CCharacter {
	CInput mInput;
	int mShootInterval;
public:
	CTexture *mpTexture;
	static CPlayer* mpInstance;
	static CShootPlayer mShootPlayer[10];

	CPlayer();
	CPlayer(float x, float y, float w, float h);

	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
