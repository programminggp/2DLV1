#include "CActionCamera.h"
#include "CKey.h"
#include "glut.h"

#define TURN_V 1.0f	//��]���x

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
	int viewport[4];
	Rotation(CVector(xaxis, yaxis, 0.0f));
	Scale(CVector(0.0f, 0.0f, distance));
	spInstance = this;
	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
	glGetIntegerv(GL_VIEWPORT, viewport);
	mScreenWidth = viewport[2];
	mScreenHeight = viewport[3];
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
	//���f���r���[�s��̎擾
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelView.M());
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());
}

CActionCamera* CActionCamera::Instance()
{
	return spInstance;
}

bool CActionCamera::WorldToScreen(CVector* screen, const CVector& world)
{
	//���W�ϊ�
	CVector modelview_pos = world * mModelView;
	CVector	screen_pos = modelview_pos * mProjection;

	//��ʊO�Ȃ̂Ń��^�[��
	if (modelview_pos.Z() >= 0.0f) {
		return false;
	}
	//���W����
	screen_pos = screen_pos * (1.0f / -modelview_pos.Z());

	//�X�N���[���ϊ�
	screen->X( (1.0f + screen_pos.X()) * mScreenWidth * 0.5f);
	screen->Y( (1.0f + screen_pos.Y()) * mScreenHeight * 0.5f);
	screen->Z( screen_pos.Z());

	return true;
}
