#ifndef CWARROK_H
#define CWARROK_H

#include "CXCharacter.h"
#include "CCollider.h"

class CWarrok : public CXCharacter
{
	CCollider mColHit;
	static CModelX mModel;
public:
	CWarrok();

	void Update();

};

#endif

