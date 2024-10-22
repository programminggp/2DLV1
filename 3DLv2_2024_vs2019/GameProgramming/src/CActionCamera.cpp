#include "CActionCamera.h"
#include "glut.h"

#define TURN_V 3.0f	//回転速度

CActionCamera* CActionCamera::spInstance = nullptr;

CActionCamera::CActionCamera()
{
	spInstance = this;
}

CActionCamera* CActionCamera::Instance()
{
	return spInstance;
}

void CActionCamera::Set(float distance, float xaxis, float yaxis)
{
	Rotation(CVector(xaxis, yaxis, 0.0f));
	Scale(CVector(0.0f, 0.0f, distance));
	mUp = CVector(0.0f, 1.0f, 0.0f);
	spInstance = this;
	int viewport[4];
	/* 現在のビューポートを保存しておく */
	glGetIntegerv(GL_VIEWPORT, viewport);
	mScreenWidth = viewport[2]; //幅を取得
	mScreenHeight = viewport[3]; //高さを取得
	//プロジェクション行列の取得
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());
	mInput.GetMousePos(&mx, &my);
}

void CActionCamera::Update()
{
	int ry = 0, rx = 0;
	if (mInput.Key('J'))
	{
		ry += TURN_V;
	}
	if (mInput.Key('L'))
	{
		ry -= TURN_V;
	}
	if (mInput.Key('I'))
	{
		rx -= TURN_V;
	}
	if (mInput.Key('K'))
	{
		rx += TURN_V;
	}

	float x, y;
	mInput.GetMousePos(&x, &y);
	ry += (mx - x);
	rx += (my - y);
	mx = x;
	my = y;

	mRotation = mRotation + CVector(0.0f, ry, 0.0f);
	mRotation = mRotation + CVector(rx, 0.0f, 0.0f);
	if (mRotation.X() < -80.0f)
	{
		mRotation.X(-80.0f);
	}
	if (mRotation.X() > 80.0f)
	{
		mRotation.X(80.0f);
	}

	//if (y != 0)
	//{
	//	mRotation = mRotation + CVector(0.0f, TURN_V, 0.0f);
	//}
	//if (y < 0)
	//{
	//	mRotation = mRotation - CVector(0.0f, TURN_V, 0.0f);
	//}
	//if (x < 0)
	//{
	//	mRotation = mRotation + CVector(x, 0.0f, 0.0f);
	//	if (mRotation.X() < -80.0f)
	//	{
	//		mRotation.X(-80.0f);
	//	}
	//}
	//if (x > 0)
	//{
	//	mRotation = mRotation + CVector(x, 0.0f, 0.0f);
	//	if (mRotation.X() > 80.0f)
	//	{
	//		mRotation.X(80.0f);
	//	}
	//}

	CTransform::Update();

	mCenter = mPosition;
	mEye = mPosition + mMatrixRotate.VectorZ() * mScale.Z();

	if (mInput.Key('N') || mInput.Key(VK_MBUTTON))
	{
		glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//		glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	if (mInput.Key('M'))
	{
		glfwSetInputMode(mInput.Window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

#include <stdio.h>

void CActionCamera::Render()
{
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
	//モデルビュー行列の取得
	glGetFloatv(GL_MODELVIEW_MATRIX, mModelView.M());

	//float x, y;
	//mInput.GetMousePos(&x, &y);
	//printf("%f,%f\n", x, y);
}

bool CActionCamera::WorldToScreen(CVector* screen, const CVector& world)
{
	//座標変換
	CVector modelview_pos = world * mModelView;
	//画面外なのでリターン
	if (modelview_pos.Z() >= 0.0f) {
		return false;
	}

	//座標調整
	CVector screen_pos = modelview_pos * mProjection;
	screen_pos = screen_pos * (1.0f / -modelview_pos.Z());

	//スクリーン変換
	screen->X((1.0f + screen_pos.X()) * mScreenWidth * 0.5f);
	screen->Y((1.0f + screen_pos.Y()) * mScreenHeight * 0.5f);
	screen->Z(screen_pos.Z());

	return true;
}

CVector CActionCamera::VectorX()
{
	return CVector(-mModelView.M(0, 0), -mModelView.M(1, 0), -mModelView.M(2, 0));
}

CVector CActionCamera::VectorZ()
{
	return CVector(-mModelView.M(0, 2), -mModelView.M(1, 2), -mModelView.M(2, 2));
}
