#ifndef CFREEMONSTER_H
#define CFREEMONSTER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CFreeMonster : public CXCharacter
{
	CCollider mColHit;
	static CModelX mModel;
public:
	CFreeMonster();

	void Update();

};

#endif

