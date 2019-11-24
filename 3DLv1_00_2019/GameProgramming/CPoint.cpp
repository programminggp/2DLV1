#include "CPoint.h"

CPoint::CPoint()
: mCollider(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.0f)
{
	mCollider.mTag = CCollider::EPOINT;
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

CPoint::CPoint(const CVector &pos)
: mCollider(this, pos, CVector(), CVector(1.0f, 1.0f, 1.0f), 1.0f)
{
	mCollider.mTag = CCollider::EPOINT;
	Set(pos);
}

void CPoint::Set(const CVector &pos) {
	mPosition = pos;
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CCharacter::Update();
}
