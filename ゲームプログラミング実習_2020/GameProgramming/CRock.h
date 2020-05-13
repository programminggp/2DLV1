//07
#ifndef CROCK_H
#define CROCK_H

#include "CCharacter.h"
#include "CCollider.h"

class CRock : public CCharacter {
public:
	CCollider mBody;
	CRock(CModel *model, const CVector &position, const CVector &rotation);
	void Collision(CCollider *mycol, CCollider *youcol);
};


#endif CROCK_H
