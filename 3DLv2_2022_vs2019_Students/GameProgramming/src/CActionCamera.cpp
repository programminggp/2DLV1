#include "CActionCamera.h"
#include "CKey.h"
#include "glut.h"

#define TURN_V 1.0f	//回転速度

CActionCamera* CActionCamera::spInstance = nullptr;

CVector CActionCamera::VectorX()
{
	return CVector(-mModelView.M(0,0), -mModelView.M(1,0), -mModelView.M(2,0));
}

CVector CActionCamera::VectorZ()
{
	return CVector(-mModelView.M(0, 2), -mModelView.M(1, 2), -mModelView.M(2, 2));
}

CActionCamera::CActionCamera(float distance, float xaxis, float yaxis)
	: mUp(0.0f, 1.0f, 0.0f)
{
	Rotation(CVector(xaxis, yaxis, 0.0f));
	Scale(CVector(0.0f, 0.0f, distance));
	spInstance = this;
}

void CActionCamera::Update()
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

void CActionCamera::Render()
{
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
	//モデルビュー行列の取得
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelView.M());
}

CActionCamera* CActionCamera::Instance()
{
	return spInstance;
}
