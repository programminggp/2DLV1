#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
#include "CInput.h"
#include "CPlayerShot.h"
#include "CTexture.h"
#include "CEffect.h"

class CPlayer : public CCharacter {
	CInput mInput;
	int mShot;
public:
	CEffect mEffect;
	CTexture *mpTexture;
	static CPlayer* mpInstance;

	CPlayer();
	CPlayer(float x, float y, float w, float h);

	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
