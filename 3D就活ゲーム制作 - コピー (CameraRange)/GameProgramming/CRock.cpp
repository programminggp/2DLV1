#include "CRock.h"

CRock::CRock(CModel *model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 9.0f)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;

}

void CRock::Collision(CCollider *m, CCollider *y){
	if (CCollider::Collision(m, y)){
		//ƒvƒŒƒCƒ„[‚ÆÚG‚·‚é‚ÆÁ–Å
		if (y->mpParent->mTag == CCharacter::EPLAYER){
			SetEnabled(false);
		}
	}
}