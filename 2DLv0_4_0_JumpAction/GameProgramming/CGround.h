#ifndef CGROUND_H
#define CGROUND_H

#include "CCharacter.h"
#include "CTexture.h"

class CGround : public CCharacter {
	CTexture *mpTexture;
public:
	CGround();
	CGround(float x, float y, float w, float h);
	void Render();
};


#endif
