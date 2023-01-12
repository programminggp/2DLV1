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
	int viewport[4];
	Rotation(CVector(xaxis, yaxis, 0.0f));
	Scale(CVector(0.0f, 0.0f, distance));
	spInstance = this;
	/* 現在のビューポートを保存しておく */
	glGetIntegerv(GL_VIEWPORT, viewport);
	mScreenWidth = viewport[2];
	mScreenHeight = viewport[3];
	//プロジェクション行列の取得
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());
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

CVector& CActionCamera::Eye()
{
	return mEye;
}

bool CActionCamera::WorldToScreen(CVector* screen, const CVector& world)
{
	//座標変換
	CVector modelview_pos = world * mModelView;
	CVector	screen_pos = modelview_pos * mProjection;

	//画面外なのでリターン
	if (modelview_pos.Z() >= 0.0f) {
		return false;
	}
	//座標調整
	screen_pos = screen_pos * (1.0f / -modelview_pos.Z());

	//スクリーン変換
	screen->X( (1.0f + screen_pos.X()) * mScreenWidth * 0.5f);
	screen->Y( (1.0f + screen_pos.Y()) * mScreenHeight * 0.5f);
	screen->Z( screen_pos.Z());

	return true;
}

void CActionCamera2::TargetEye(const CVector& eye)
{
	mTargetEye = eye;
}

void CActionCamera2::TargetCenter(const CVector& center)
{
	mTargetCenter = center;
}

CActionCamera2::CActionCamera2(float distance, float xaxis, float yaxis)
	: CActionCamera(distance, xaxis, yaxis)
{
}

#define VELOCITY_CAMERA 0.09f

void CActionCamera2::Update()
{
	CVector oldCenter = mCenter;
	CVector oldEye = mEye;

	CActionCamera::Update();
	
	CVector dirCenter = (mCenter - oldCenter);
	CVector dirEye = (mEye - oldEye);
	if (dirCenter.Length() > VELOCITY_CAMERA)
	{
		mCenter = oldCenter + dirCenter.Normalize() * VELOCITY_CAMERA;
	}
	if (dirEye.Length() > VELOCITY_CAMERA)
	{
		mEye = oldEye + dirEye.Normalize() * VELOCITY_CAMERA;
	}
}