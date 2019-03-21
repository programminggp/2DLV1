#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "CRectangle.h"

class CCharacter : public CRectangle {
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
	ETag mTag;
};

#endif
