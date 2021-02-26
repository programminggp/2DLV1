#ifndef CSPHERE_H
#define CSPHERE_H

#include "CObj.h"

class CSphere : public CObj
{
//	CVector mG;
	CVector mVelocity;
	CCollider mCollider;
public:
	CSphere(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale);
	void Update();
	void Collision(CCollider *m, CCollider *o);
};

#endif
