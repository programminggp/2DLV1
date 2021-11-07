#include "CCameraControl.h"
#include "CKey.h"
#include "CXPlayer.h"

#define FOWARD  7.0f
#define UP CVector(0.0f, 1.0f, 0.0f)
#define VELOCITY 0.5f
//#define START_POSITION CVector(0.0f, 3.0f, 10.0f)
#define HEAD_ADJUST CVector(0.0f, 3.0f, 0.0f)

CCameraControl::CCameraControl()
	: mDistance(0.0f, 0.0f, 1.0f)
{
	mPosition = CVector(0.0f, 0.0f, 0.0f);
	mRotation = CVector(0.0f, 0.0f, 0.0f);
	CTransform::Update();
//	mCamera.Set(mPosition, mPosition + FOWARD * mMatrixRotate, UP * mMatrixRotate);
	mCamera.Set(mPosition + mDistance * mMatrixRotate, mPosition + HEAD_ADJUST, UP * mMatrixRotate);
}

CCameraControl::CCameraControl(const CVector& pos, const CVector& rot, float dis)
	: mDistance(0.0f, 4.0f, dis)
{
	mPosition = pos;
	mRotation = rot;
	CTransform::Update();
	//	mCamera.Set(mPosition, mPosition + FOWARD * mMatrixRotate, UP * mMatrixRotate);
	mCamera.Set(mPosition + mDistance * mMatrixRotate, mPosition, UP * mMatrixRotate);
}

void CCameraControl::Update()
{
	mPosition = CXPlayer::spInstance->mPosition;
	if (CKey::Push(VK_SHIFT))
	{
		mPosition = mPosition + mDistance * VELOCITY * mMatrixRotate;
	}
	if (CKey::Push(VK_CONTROL))
	{
		mPosition = mPosition - mDistance * VELOCITY * mMatrixRotate;
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
//	mCamera.Set(mPosition, mPosition + FOWARD * mMatrixRotate, UP * mMatrixRotate);
	mCamera.Set(mPosition + mDistance * mMatrixRotate, mPosition + HEAD_ADJUST, UP * mMatrixRotate);
	mCamera.Render();
}

void CCameraControl::Render()
{
//	printf("x:%f y:%f z:%f\n", mPosition.mX, mPosition.mY, mPosition.mZ);
}
