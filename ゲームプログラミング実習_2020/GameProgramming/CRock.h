//07
#ifndef CROCK_H
#define CROCK_H

#include "CCharacter.h"
#include "CCollider.h"

class CRock : public CCharacter {
public:
	CCollider mColBody;
	CRock(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale);
	void Collision(CCollider *mycol, CCollider *youcol);
};


#endif CROCK_H
