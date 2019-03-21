#ifndef CEFFECT_H
#define CEFFECT_H

#include "CCharacter.h"

class CEffect : public CCharacter {
public:
	int mIndex;
	CEffect();
	CEffect(int posx, int posy, int width, int height);
	void Update();
	void Render();
};

#endif
