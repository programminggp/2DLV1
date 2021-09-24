#ifndef CFELGUARD_H
#define CFELGUARD_H

#include "CXCharacter.h"
#include "CCollider.h"

class CFelguard : public CXCharacter
{
	CCollider mColHit;
	static CModelX mModel;
public:
	CFelguard();

	void Update();

};

#endif

