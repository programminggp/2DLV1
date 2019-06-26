#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
#include "CInput.h"
#include "CShootPlayer.h"
#include "CTexture.h"

class CPlayer : public CCharacter {
	CInput mInput;
	int mShootInterval;
public:
	CTexture *mpTexture;
	float mX, mY, mW, mH;
	static CPlayer* mpInstance;

	CPlayer();
	CPlayer(float x, float y, float w, float h);
	void Set(float x, float y, float w, float h);

	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
