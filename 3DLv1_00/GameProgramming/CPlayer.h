#ifndef CPLAYER
#define CPLAYER

#include "CCharacter.h"

class CPlayer : public CCharacter {
public:
	static CPlayer *mpPlayer;
	CPlayer();
	~CPlayer();
	void Update();
};

#endif
