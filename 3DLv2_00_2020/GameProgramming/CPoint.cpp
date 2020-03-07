#include "CPoint.h"

CPoint::CPoint()
: mCollider(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.0f)
{
	mTag = EPOINT;
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

//CPoint::CPoint(const CVector &pos, float r)
//: mCollider(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.0f)
//{
//	mTag = EPOINT;
//	Set(pos, r);
//}

void CPoint::Set(const CVector &pos, float r) {
	mPosition = pos;
	mCollider.mRadius = r;
	CCharacter::Update();
}
