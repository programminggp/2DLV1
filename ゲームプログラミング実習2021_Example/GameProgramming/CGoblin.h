#ifndef CGOBLIN_H
#define CGOBLIN_H

#include "CXCharacter.h"
#include "CCollider.h"

class CGoblin : public CXCharacter
{
	CCollider mColHit;
	static CModelX mModel;
public:
	CGoblin();

	void Update();

};

#endif

