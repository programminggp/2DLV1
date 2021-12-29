#define _USE_MATH_DEFINES
#include <math.h>
#include "CCamera.h"
#include "CKey.h"
#include "glut.h"

//ÉJÉÅÉâÇÃäOïîïœêî
//CCamera Camera;

CCamera* CCamera::spInstance = nullptr;

CCamera* CCamera::Get()
{
	return spInstance;
}

CCamera::CCamera(const CVector& pos, const CVector& rot, float distance)
	: CCharacter(10)
{
	spInstance = this;
	Position(pos);
	Rotation(rot);
	Scale(CVector(distance, distance, distance));
}

const CVector& CCamera::Eye() const
{
	return mEye;
}

void CCamera::Set(const CVector &eye, const CVector &center,
	const CVector &up) {
	mEye = eye;
	mCenter = center;
	mUp = up;
}

void CCamera::Update()
{
	if (CKey::Push('J'))
	{
		mRotation.Y(mRotation.Y() + 2.0f);
	}
	if (CKey::Push('L'))
	{
		mRotation.Y(mRotation.Y() - 2.0f);
	}
}

void CCamera::Render() {

	CVector dist(sinf(mRotation.Y() / 180.0f * M_PI + M_PI) * mScale.Z()
		, sinf(mRotation.X() / 180.0f * M_PI) * mScale.Z()
		, cosf(mRotation.Y() / 180.0f * M_PI + M_PI) * mScale.Z());
	mCenter = mPosition;
	mEye = mCenter + dist;
	mUp = CVector(sinf(mRotation.Y() / 180.0f * M_PI)
		, cosf(mRotation.X() / 180.0f * M_PI)
		, cosf(mRotation.Y() / 180.0f * M_PI));

	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
}
