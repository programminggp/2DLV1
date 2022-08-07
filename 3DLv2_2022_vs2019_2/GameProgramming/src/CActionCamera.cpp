#include "CActionCamera.h"
#include "CTaskManager.h"
#include "CKey.h"
#include "glut.h"

#define TURN_V 1.0f	//‰ñ“]‘¬“x

CActionCamera* CActionCamera::spInstance = nullptr;

CActionCamera::CActionCamera(float distance)
	: mUp(0.0f, 1.0f, 0.0f)
{
	Rotation(CVector(5.0f, 0.0f, 0.0f));
	Scale(CVector(0.0f, 0.0f, distance));
	spInstance = this;
	CTaskManager::Get()->Remove(this);
	mPriority = 0;
	CTaskManager::Get()->Add(this);
}

void CActionCamera::CameraUpdate()
{
	if (CKey::Push('J'))
	{
		mRotation = mRotation + CVector(0.0f, TURN_V, 0.0f);
	}
	if (CKey::Push('L'))
	{
		mRotation = mRotation - CVector(0.0f, TURN_V, 0.0f);
	}
	if (CKey::Push('I'))
	{
		mRotation = mRotation - CVector(TURN_V, 0.0f, 0.0f);
		if (mRotation.X() < -80.0f)
		{
			mRotation.X(-80.0f);
		}
	}
	if (CKey::Push('K'))
	{
		mRotation = mRotation + CVector(TURN_V, 0.0f, 0.0f);
		if (mRotation.X() > 80.0f)
		{
			mRotation.X(80.0f);
		}
	}
	CTransform::Update();
	mCenter = mPosition;
	mEye = mPosition + mMatrixRotate.VectorZ() * mScale.Z();
}

void CActionCamera::CameraRender() {

	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
}

CActionCamera* CActionCamera::Instance()
{
	return spInstance;
}
