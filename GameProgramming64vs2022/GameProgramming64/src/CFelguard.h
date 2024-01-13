#ifndef CFELGUARD_H
#define CFELGUARD_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CColliderCapsule.h"
#include "CColliderLine.h"

class CFelguard : public CXCharacter
{
	CCollider mColHit;
//	CColliderCapsule mColCapsule;
	CColliderLine mColCapsule;
	static CModelX mModel;
public:
	CFelguard();

	void Update();

	void ChangeState(EState state);

	void TaskCollision();
	void Collision(CCollider* m, CCollider* o);

};

#endif

