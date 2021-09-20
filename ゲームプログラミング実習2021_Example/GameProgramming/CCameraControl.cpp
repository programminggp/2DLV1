#include "CCameraControl.h"
#include "CKey.h"

#define FOWARD CVector(0.0f, 0.0f, 1.0f)
#define UP CVector(0.0f, 1.0f, 0.0f)
#define VELOCITY 0.1f
#define START_POSITION CVector(0.0f, 0.0f, 15.0f)

CCameraControl::CCameraControl()
{
	mPosition = START_POSITION;
	mRotation = CVector(0.0f, 180.0f, 0.0f);
	CTransform::Update();
	mCamera.Set(mPosition, mPosition + FOWARD * mMatrixRotate, UP * mMatrixRotate);
}

void CCameraControl::Update()
{
	if (CKey::Push(VK_SHIFT))
	{
		mPosition = mPosition + FOWARD * VELOCITY * mMatrixRotate;
	}
	if (CKey::Push(VK_CONTROL))
	{
		mPosition = mPosition - FOWARD * VELOCITY * mMatrixRotate;
	}
	if (CKey::Push(VK_RIGHT))
	{
		mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f);
	}
	if (CKey::Push(VK_LEFT))
	{
		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f);
	}
	if (CKey::Push(VK_UP))
	{
		mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f);
	}
	if (CKey::Push(VK_DOWN))
	{
		mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f);
	}
	CTransform::Update();
	mCamera.Set(mPosition, mPosition + FOWARD * mMatrixRotate, UP * mMatrixRotate);
	mCamera.Render();
}
