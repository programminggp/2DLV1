#ifndef CCOLLIDER
#define CCOLLIDER

#include "CVector.h"
#include "CTask.h"

class CCharacter;

class CCollider : public CTask {
public:
	CVector mV[1];
	float mRadius;
	CCharacter *mpParent;

	CCollider();
	~CCollider();

	void Render();
	static bool Collision(CCollider *, CCollider *);

};


#endif
