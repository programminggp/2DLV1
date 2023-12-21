#define _USE_MATH_DEFINES
#include <math.h>
#include "CCamera.h"
#include "CKey.h"
#include "gl/freeglut.h"

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
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());
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
	if (CKey::Push('I'))
	{
		mRotation.X(mRotation.X() - 2.0f);
	}
	if (CKey::Push('K'))
	{
		mRotation.X(mRotation.X() + 2.0f);
	}
	mVectorZ.Set(sinf(mRotation.Y() / 180.0f * M_PI)
		, -sinf(mRotation.X() / 180.0f * M_PI)
		, cosf(mRotation.Y() / 180.0f * M_PI));
	mVectorX.Set(cosf(mRotation.Y() / 180.0f * M_PI)
		, 0.0f
		, -sinf(mRotation.Y() / 180.0f * M_PI));
	mCenter = mPosition;
	mEye = mCenter + mVectorZ * -mScale.Z();
	mVectorZ.Y(0.0f);
	mUp = CVector(sinf(mRotation.Y() / 180.0f * M_PI)
		, cosf(mRotation.X() / 180.0f * M_PI)
		, cosf(mRotation.Y() / 180.0f * M_PI)).Normalize();
}

void CCamera::Render() {



	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelView.M());
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());
}

const CVector& CCamera::VectorZ()
{
	return mVectorZ;
}

const CVector& CCamera::VectorX()
{
	return mVectorX;
}
