#ifndef CBULLET
#define CBULLET

#include "CCharacter.h"
#include "CBox.h"
#include "CCollider.h"

class CBullet : public CCharacter {
public:
	CTriangle mT[2];
	CBox mBox;
	int mLife;
	CCollider mCollider;

	CBullet();

	void Set(float x, float y, float z, float w, float h, float d);
	void SetDiffuse(float r, float g, float b, float a);
	void Update();
	void Render();
};

#endif
