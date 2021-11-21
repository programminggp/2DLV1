#ifndef CSCORPID_H
#define CSCORPID_H

#include "CXCharacter.h"
#include "CCollider.h"

class CScorpid : public CXCharacter
{
	CCollider mColHit;
	static CModelX mModel;
public:
	CScorpid();

	void Update();

};

#endif

