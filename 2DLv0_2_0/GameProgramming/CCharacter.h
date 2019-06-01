#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "CRectangle.h"
#include "CTask.h"

class CCharacter : public CRectangle, public CTask {
public:
	enum ETag {
		ENONE,
		EPLAYER,
		EBACKGROUND,
		EBOSS,
		ESHOOTPLAYER,
		ESHOOTBOSS,
		EENEMY
	};
	
	CCharacter() {
		Enable();
	}

	ETag mTag;
};

#endif
