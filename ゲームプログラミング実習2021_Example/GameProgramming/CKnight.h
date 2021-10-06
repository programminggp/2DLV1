#ifndef CKNIGHT_H
#define CKNIGHT_H

#include "CXCharacter.h"
#include "CCollider.h"

class CKnight : public CXCharacter
{
	CCollider mColHit;
	static CModelX mModel;
public:
	CKnight();
	CKnight(const CVector& pos, const CVector& rot, const CVector& scale);

	void Update();

};

#endif

