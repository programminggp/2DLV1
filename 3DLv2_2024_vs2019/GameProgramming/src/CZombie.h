#ifndef CZOMBIE_H
#define CZOMBIE_H

#include "CXCharacter.h"
#include "CColliderCapsule.h"

class CZombie : public CXCharacter
{
public:
	CZombie();
	CZombie(const CVector& pos, const CVector& rot, const CVector& scale );
	void Update();
private:
	CColliderCapsule mColBody;	//‘Ì
	static CModelX sModel;
};

#endif

