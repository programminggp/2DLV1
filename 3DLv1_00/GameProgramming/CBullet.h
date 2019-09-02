#ifndef CBULLET
#define CBULLET

#include "CCharacter.h"
#include "CBox.h"

class CBullet : public CCharacter {
public:
	CBox mBox;
	int mLife;

	CBullet();

	void Set(float x, float y, float z, float w, float h, float d);
	void SetDiffuse(float r, float g, float b, float a);
	void Update();
	void Render();
};

#endif
