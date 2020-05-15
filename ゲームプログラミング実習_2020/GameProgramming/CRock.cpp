//07
#include "CRock.h"

CRock::CRock(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 9.0f)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
}

void CRock::Collision(CCollider *mycol, CCollider *youcol) {
	if (CCollider::Collision(mycol, youcol)) {
		mEnabled = false;
	}
}