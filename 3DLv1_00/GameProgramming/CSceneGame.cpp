#include "CSceneGame.h"
#include "glut.h"
#include "CTriangle.h"

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
	mModel.Load("f14.obj", "f14.mtl");
//	mModel.Load("mini.obj", "mini.mtl");
	mSky.Load("sky.obj", "sky.mtl");
	CMatrix().print();
	mCharacter.Init(&mModel, 8.0f, 1.0f, 2.0f, -60.0f, 90.0f, 0.0f, 0.2f, 0.2f, 0.2f);
}

void CSceneGame::Update() {
	mDegree++;
	mMatrix.RotateY(mDegree);
	//gluLookAt(	mCameraEye.mX, mCameraEye.mY, mCameraEye.mZ, 
	//			mCameraCenter.mX, mCameraCenter.mY, mCameraCenter.mZ,
	//			mCameraUp.mX, mCameraUp.mY, mCameraUp.mZ);

	mCamera.mEye = mCamera.mEye * CMatrix().RotateY(1);
	mCamera.Render();

	float mDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
//	mTriangle[0].Render(mMatrix);
//	mTriangle[1].Render(mMatrix);
//	mRectangle.Render(mMatrix);
//	mBox.Render(mMatrix);

	CMatrix scale, rotate, translate;
	scale.Scale(0.2f, 0.2f, 0.2f);
	rotate.RotateZ(mDegree);
	translate.Translate(2.0f, 3.0f, -4.0f);

	mMatrix = scale * rotate * translate;
//	mModel.Render(mMatrix);

	translate.Translate(0.0f, 0.0f, 0.0f);
	mMatrix = scale * rotate * translate;
	mModel.Render(mMatrix);

	mSky.Render(CMatrix());

	mCharacter.Update();
	mCharacter.Render();

}

//デストラクタ
CSceneGame::~CSceneGame() {

}
