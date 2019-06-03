#ifndef CEFFECT_H
#define CEFFECT_H

#include "CCharacter.h"

class CEffect : public CCharacter {
public:
	static CTexture mTexture;
	int mIndex;
	CEffect();
	CEffect(float x, float y, float w, float h);
	void Update();
	void Render();
};

#endif
