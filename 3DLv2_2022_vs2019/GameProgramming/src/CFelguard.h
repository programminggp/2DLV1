#ifndef CFELGUARD_H
#define CFELGUARD_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CColliderCapsule.h"

class CFelguard : public CXCharacter
{
	CCollider mColHit;
	CColliderCapsule mColCapsule;
	static CModelX mModel;
public:
	CFelguard();

	void Update();

};

#endif

