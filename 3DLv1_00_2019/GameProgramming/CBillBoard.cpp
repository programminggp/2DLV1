#include "CBillBoard.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>

CBillBoard::CBillBoard() {
}

CBillBoard::CBillBoard(CVector pos, float w, float h) {
	Set(pos, w, h);
}

void CBillBoard::Set(CVector pos, float w, float h) {
	mPosition = pos;
	mScale.mX = w;
	mScale.mY = h;
	//Vertex
	mT[0].SetVertex(CVector(1.0f, 1.0f, 0.0f), CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, -1.0f, 0.0f));
	mT[1].SetVertex(CVector(-1.0f, 1.0f, 0.0f), CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, 1.0f, 0.0f));
	//Normal
	mT[0].SetNormal(CVector(0.0f, 0.0f, 1.0f));
	mT[1].SetNormal(CVector(0.0f, 0.0f, 1.0f));
	//White
	mMaterial.mDiffuse[0] = mMaterial.mDiffuse[1] = mMaterial.mDiffuse[2] = mMaterial.mDiffuse[3] = 1.0f;
}

void CBillBoard::Update() {
	CVector dir = (Camera.mEye - mPosition).Normalize();
	mRotation.mY = atan2f(dir.mX, dir.mZ) * 180.0f / M_PI;
	mRotation.mX = asinf(-dir.mY) * 180.0f / M_PI;
	CCharacter::Update();
}

void CBillBoard::Render() {
	glPushMatrix();
	glMultMatrixf(mMatrix.mM[0]);
	glDisable(GL_LIGHTING);
	glColor4fv(mMaterial.mDiffuse);
	mT[0].Render();
	mT[1].Render();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

