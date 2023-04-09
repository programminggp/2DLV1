#include "CActionCamera.h"
#include "CKey.h"
#include"CInput.h"
#include "glut.h"

#define TURN_V 10.0f	//��]���x

CActionCamera* CActionCamera::spInstance = nullptr;

CActionCamera* CActionCamera::Instance()
{
	return spInstance;
}

CVector CActionCamera::VectorX()
{
	return CVector(-mModelView.M(0, 0), -mModelView.M(1, 0), -mModelView.M(2, 0));
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
	int w = CInput::Wheel();
	if (w != 0){
		if (w > 0){
			mRotation = mRotation + CVector(0.0f, TURN_V, 0.0f);
		}
		else{
			mRotation = mRotation - CVector(0.0f, TURN_V, 0.0f);
		}
	}
	/*if (CKey::Push('J'))
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
	}*/
	CTransform::Update();
	mCenter = mPosition;
	mEye = mPosition + mMatrixRotate.VectorZ() * mScale.Z();
}

void CActionCamera::Render()
{
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
	//���f���r���[�s��̎擾
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelView.M());
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mModelViewInv.M(i, j, mModelView.M(j,i));
		}
	}
}

const CMatrix& CActionCamera::ModelView()
{
	return mModelView;
}

const CMatrix& CActionCamera::ModelViewInv()
{
	return mModelViewInv;
}