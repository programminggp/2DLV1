#ifndef CBLOCK_H
#define CBLOCK_H

#include "CCharacter.h"

class CBlock : public CCharacter {
public:
	CTexture *mpTexture;
	CBlock();
	CBlock(float x, float y, float w, float h);
	void Render();
};

#endif
