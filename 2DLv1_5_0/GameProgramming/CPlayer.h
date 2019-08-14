#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
#include "CInput.h"
#include "CTexture.h"

class CPlayer : public CCharacter {
	CTexture *mpTexture;
	CInput mInput;
	int mShootInterval;
	float mFx, mFy;
	float mPx, mPy;
	bool mIsAlive;
	int mFrame;
public:
	static CPlayer* mpInstance;

	CPlayer();
	CPlayer(float x, float y, float w, float h);

	void Update();
	void Render();
	void Collision(CCharacter* my, CCharacter* you);
};

#endif
