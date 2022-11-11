#ifndef CPALADIN_H
#define CPALADIN_H

#include "CXCharacter.h"
#include "CColliderCapsule.h"

class CPaladin : public CXCharacter
{
public:
	void Update();
	CPaladin(CVector pos, CVector rot, CVector scale);
	void Init(CModelX* model);

private:
	CColliderCapsule mColCapsule;

};

#endif
