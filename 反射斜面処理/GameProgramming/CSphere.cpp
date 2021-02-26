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

				//面の法線を求める
				adjust = adjust.Normalize();
				//法線と速度の内積を求める
				float dot = adjust.Dot(mVelocity);
				//内積の大きさの法線を求める
				adjust = adjust * dot * -1.0f;
				//法線に対して横向きのベクトルを求める
//				mVelocity = adjust + mVelocity;
				//法線と横向きのベクトルで反射ベクトルを求める
//				mVelocity = adjust + mVelocity;
				//反射ベクトルを求める
				mVelocity = mVelocity + adjust * 2;

			}
		}
	}
}
