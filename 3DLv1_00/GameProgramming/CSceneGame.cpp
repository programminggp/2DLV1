#include "CSceneGame.h"
#include "glut.h"
#include "CTriangle.h"
#include "CKey.h"
#include "CTaskManager.h"
#include "CEnemy.h"
#include "CFire.h"

CFire Fire;

CTaskManager TaskManager;

//CSceneGame::CSceneGame() {}

void CSceneGame::Init() {
	mCameraEye.Set(1.0f, 3.0f, 5.0f);
	mCameraCenter.Set(0.0f, 0.0f, 0.0f);
	mCameraUp.Set(0.0f, 1.0f, 0.0f);
	mTriangle[0].SetVertex(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	mTriangle[0].SetNormal(0.0f, 0.0f, 1.0f);
	mTriangle[1].SetVertex(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	mTriangle[1].SetNormal(0.0f, 0.0f, 1.0f);
	mRectangle.SetVertex(0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f);
	mRectangle.SetNormal(0.0f, 1.0f, 0.0f);
	mDegree = 0.0f;
//	mBox.Set(0.0f, -2.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	mBox.Set(0.0f, -1.0f, 0.0f, 0.7f, 0.2f, 1.0f);
	//mModel.Load("f16.obj", "f16.mtl");
	mModel.Load("f14.obj", "f14.mtl");
	//mModel.Load("mini.obj", "mini.mtl");
	mSky.Load("sky.obj", "sky.mtl");
	mF16.Load("f16.obj", "f16.mtl");
	CMatrix().print();
	mCharacter.Init(&mModel, 8.0f, 1.0f, 2.0f, -60.0f, 90.0f, 0.0f, 0.2f, 0.2f, 0.2f);
	mPlayer.Init(&mModel, 0.0f, 1.0f, -8.0f, 0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 0.2f);
	//mBullet.Set(0.0f, 0.0f, 0.0f, 0.1f, 0.1f, 0.3f);
	//mBullet.SetDiffuse(1.0f, 1.0f, 0.0f, 1.0f);
	new CEnemy(&mF16, 0.0f, 5.0f, 4.0f, 0.0f, 90.0f, -30.0f, 0.2f, 0.2f, 0.2f);
	new CEnemy(&mF16, 0.0f, 7.0f, 6.0f, 0.0f, 90.0f, -30.0f, 0.2f, 0.2f, 0.2f);

	Fire.mPosition = CVector(0.0f, 1.0f, 3.0f);
	Fire.mRotation.mY = -90.0f;
	Fire.SetTexture("fire.tga");
}

void CSceneGame::Update() {
	//mDegree++;
	//mMatrix.RotateY(mDegree);
	//gluLookAt(	mCameraEye.mX, mCameraEye.mY, mCameraEye.mZ, 
	//			mCameraCenter.mX, mCameraCenter.mY, mCameraCenter.mZ,
	//			mCameraUp.mX, mCameraUp.mY, mCameraUp.mZ);

	mPlayer.Update();
	//if (CKey::Push(VK_SPACE)) {
	//	mBullet.mPosition = mPlayer.mPosition;
	//	mBullet.mRotation = mPlayer.mRotation;
	//}
//	mBullet.Update();

	TaskManager.Update();

//	mCamera.mEye = mCamera.mEye * CMatrix().RotateY(1);
	mCamera.mEye = mPlayer.mPosition + CVector(0.0f, 2.0f, -6.0f) * mPlayer.mMatrixRotation;
	mCamera.mCenter = mPlayer.mPosition;
	mCamera.mUp = CVector(0.0f, 1.0f, 0.0f) * mPlayer.mMatrixRotation;
	mCamera.Render();

	//float mDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	//mTriangle[0].Render(mMatrix);
	//mTriangle[1].Render(mMatrix);
	//mRectangle.Render(mMatrix);
	//mBox.Render(mMatrix);

	//CMatrix scale, rotate, translate;
	//scale.Scale(0.2f, 0.2f, 0.2f);
	//rotate.RotateZ(mDegree);
	//translate.Translate(2.0f, 3.0f, -4.0f);

	//mMatrix = scale * rotate * translate;
	//mModel.Render(mMatrix);

	//translate.Translate(0.0f, 0.0f, 0.0f);
	//mMatrix = scale * rotate * translate;
//	mModel.Render(mMatrix);

	mSky.Render(CMatrix());

	//mCharacter.Update();
	//mCharacter.Render();

	mPlayer.Render();
//	mBullet.Render();

	TaskManager.Delete();
	TaskManager.Render();

	Fire.Update();
	Fire.Render();

}

//デストラクタ
CSceneGame::~CSceneGame() {
	TaskManager.Destory();
}
