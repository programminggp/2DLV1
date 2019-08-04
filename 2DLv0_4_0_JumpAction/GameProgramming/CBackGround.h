#ifndef CBACKGROUNG_H
#define CBACKGROUNG_H

#include "CCharacter.h"
#include "CTexture.h"

class CBackGround : public CCharacter {
	CTexture *mpTexture;
public:
	CRectangle r1, r2, r3, r4;
	CBackGround();
	CBackGround(float x, float y, float w, float h);
	void Render();
};


#endif
