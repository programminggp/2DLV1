#ifndef CPALADIN_H
#define CPALADIN_H

#include "CXCharacter.h"
#include "CColliderCapsule.h"

class CPaladin : public CXCharacter
{
public:
	void Render();
	void Update();
	CPaladin(CVector pos, CVector rot, CVector scale);
	void Init(CModelX* model);
	void TaskCollision();
	void Collision(CCollider *m, CCollider* o);
private:
	CColliderCapsule mColCapsule;

};

#endif
