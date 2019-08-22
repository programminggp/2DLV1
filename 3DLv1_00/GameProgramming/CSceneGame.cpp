#include "CSceneGame.h"
#include "glut.h"
#include "CTriangle.h"

//CSceneGame::CSceneGame() {}

void CSceneGame::Init() {
	mCameraEye.Set(1.0f, 3.0f, 25.0f);
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
}

void CSceneGame::Update() {
	mDegree++;
	mMatrix.RotateY(mDegree);
	gluLookAt(	mCameraEye.mX, mCameraEye.mY, mCameraEye.mZ, 
				mCameraCenter.mX, mCameraCenter.mY, mCameraCenter.mZ,
				mCameraUp.mX, mCameraUp.mY, mCameraUp.mZ);
	float mDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	mTriangle[0].Render(mMatrix);
	mTriangle[1].Render(mMatrix);
	mRectangle.Render(mMatrix);
	mBox.Render(mMatrix);
	mModel.Render(mMatrix);
}

//�f�X�g���N�^
CSceneGame::~CSceneGame() {

}