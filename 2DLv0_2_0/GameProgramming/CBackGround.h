#ifndef CBACKGROUNG_H
#define CBACKGROUNG_H

#include "CCharacter.h"
#include "CTexture.h"

class CBackGround : public CCharacter {
public:
	CTexture mTexture;
	CBackGround();
	void Render();
};


#endif
