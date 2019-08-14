#ifndef CBLOCK_H
#define CBLOCK_H

#include "CCharacter.h"
#include "CTexture.h"

class CBlock : public CCharacter {
	CTexture *mpTexture;
public:
	CBlock();
	CBlock(float x, float y, float w, float h);
	void Render();
};

#endif
