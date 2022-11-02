#include "CActionCamera.h"
#include "CTaskManager.h"
#include "CKey.h"
#include "glut.h"

#define TURN_V 1.0f	//回転速度

CActionCamera* CActionCamera::spInstance = nullptr;
CMatrix CActionCamera::mModelViewInverse;
CMatrix CActionCamera::mModelView;

const CMatrix& CActionCamera::ModelViewInverse()
{
	return mModelViewInverse;
}

const CMatrix& CActionCamera::ModelView()
{
	return mModelView;
}

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

CActionCamera::CActionCamera(float distance, float xaxis, float yaxis)
	: mUp(0.0f, 1.0f, 0.0f)
{
	Rotation(CVector(xaxis, yaxis, 0.0f));
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
	//モデルビュー行列の取得
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelView.M());
	//逆行列の取得
	mModelViewInverse = mModelView.Transpose();
	mModelViewInverse.M(0, 3, 0);
	mModelViewInverse.M(1, 3, 0);
	mModelViewInverse.M(2, 3, 0);
}

CActionCamera* CActionCamera::Instance()
{
	return spInstance;
}
