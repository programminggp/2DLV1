#include "CCamera.h"
#include "CTaskManager.h"
#include "CKey.h"
#include "glut.h"

//ƒJƒƒ‰‚ÌŠO•”•Ï”
//CCamera Camera;
CCamera* CCamera::spInstance = nullptr;

CCamera::CCamera(float distance)
	: mUp(0.0f, 1.0f, 0.0f)
{
	Rotation(CVector(5.0f, 0.0f, 0.0f));
	Scale(CVector(0.0f, 0.0f, distance));
	spInstance = this;
	CTaskManager::Get()->Remove(this);
	mPriority = 10;
	CTaskManager::Get()->Add(this);
}

void CCamera::Center(CVector& center)
{
	mCenter = center;
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

void CCamera::Render() {
	if (CKey::Push('J'))
	{
		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f);
	}
	if (CKey::Push('L'))
	{
		mRotation = mRotation - CVector(0.0f, 1.0f, 0.0f);
	}
	if (CKey::Push('I'))
	{
		mRotation = mRotation - CVector(1.0f, 0.0f, 0.0f);
		if (mRotation.X() < -80.0f)
		{
			mRotation.X(-80.0f);
		}
	}
	if (CKey::Push('K'))
	{
		mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f);
		if (mRotation.X() > 80.0f)
		{
			mRotation.X(80.0f);
		}
	}
	CTransform::Update();
	mCenter = mPosition;
	mEye = mPosition + mMatrixRotate.VectorZ() * mScale.Z();
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
}

CCamera* CCamera::Instance()
{
	return spInstance;
}
