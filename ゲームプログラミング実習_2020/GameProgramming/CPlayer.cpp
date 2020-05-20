#include "CPlayer.h"
#include "CKey.h"

void CPlayer::Update() {
	if (CKey::Push('A')) {
		mRotation.mY++;
	}
	if (CKey::Push('D')) {
		mRotation.mY--;
	}
	//5
	if (CKey::Push('W')) {
		mPosition = CVector(0.0f, 0.0f, 0.5f) * mMatrix;
	}
	CCharacter::Update();
}

CPlayer::CPlayer()
//ƒRƒ‰ƒCƒ_‚Ì‰ŠúÝ’è
: mColBody(this, CVector(0.0f, 4.0f, -1.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 9.0f)
{
}

void CPlayer::Collision(CCollider *mycol, CCollider *youcol) {
	CVector adjust;
	if (mycol->mType == CCollider::ESPHERE) {
		if (youcol->mType == CCollider::ETRIANGLE) {
			if (CCollider::CollisionTriangleSphere(youcol, mycol, &adjust)) {
				mPosition = mPosition + adjust;
				CCharacter::Update();
			}
		}
	}
}
