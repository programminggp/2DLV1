#ifndef CPOINT_H
#define CPOINT_H

#include "CCollider.h"
#include "CCharacter.h"

class CPoint : public CCharacter {
public:
	CCollider mCollider;
	CPoint();
	CPoint(const CVector &pos);

	void Set(const CVector &pos);

};


#endif
