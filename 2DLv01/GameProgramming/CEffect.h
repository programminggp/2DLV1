#ifndef CEFFECT_H
#define CEFFECT_H

#include "CCharacter.h"

class CEffect : public CCharacter {
public:
	int mIndex;
	CEffect();
	void Update();
	void Render();
};

#endif
