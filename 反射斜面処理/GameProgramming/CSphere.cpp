#include "CSphere.h"
#include "CKey.h"

//#define GRAVITY CVector(0.0f, 0.01f, 0.0f)
#define GRAVITY CVector(0.0f, 0.0f, 0.0f)

CSphere::CSphere(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:mCollider(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), scale.mX)
, mVelocity(0.0f, -0.1f, 0.0f)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
}

void CSphere::Update()
{
	if (CKey::Push(' '))
	{
		mPosition = CVector(0.0f, 20.0f, 0.0f);
		mVelocity = CVector(0.0f, -0.1f, 0.0f);
	}
	mVelocity = mVelocity - GRAVITY;
	mPosition = mPosition + mVelocity;
	CCharacter::Update();
}

void CSphere::Collision(CCollider *mcol, CCollider *ycol) {
	CVector adjust;
	if (mcol->mType == CCollider::ESPHERE) {
		if (ycol->mType == CCollider::ETRIANGLE) {
			if (CCollider::CollisionTriangleSphere(ycol, mcol, &adjust)) {
				mPosition = mPosition + adjust;
				CCharacter::Update();
//				mVelocity = mVelocity * -1.0f;

				//�ʂ̖@�������߂�
				adjust = adjust.Normalize();
				//�@���Ƒ��x�̓��ς����߂�
				float dot = adjust.Dot(mVelocity);
				//���ς̑傫���̖@�������߂�
				adjust = adjust * dot * -1.0f;
				//�@���ɑ΂��ĉ������̃x�N�g�������߂�
//				mVelocity = adjust + mVelocity;
				//�@���Ɖ������̃x�N�g���Ŕ��˃x�N�g�������߂�
//				mVelocity = adjust + mVelocity;
				//���˃x�N�g�������߂�
				mVelocity = mVelocity + adjust * 2;

			}
		}
	}
}
