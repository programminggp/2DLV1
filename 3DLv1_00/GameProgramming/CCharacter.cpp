#include "CCharacter.h"

CCharacter::CCharacter()
: mScale(1.0f, 1.0f, 1.0f)
, mpModel(0)
{

}

CCharacter::~CCharacter() {
}

void CCharacter::Init(CModel *model, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz)
{
	mpModel = model;
	mPosition = CVector(px, py, pz);
	mRotation = CVector(rx, ry, rz);
	mScale = CVector(sx, sy, sz);
}

void CCharacter::Update() {
	mMatrix = CMatrix().Scale(mScale.mX, mScale.mY, mScale.mZ);
	mMatrixRotation = CMatrix().RotateZ(mRotation.mZ);
	mMatrixRotation = mMatrixRotation * CMatrix().RotateX(mRotation.mX);
	mMatrixRotation = mMatrixRotation * CMatrix().RotateY(mRotation.mY);
	mMatrix = mMatrix * mMatrixRotation * CMatrix().Translate(mPosition.mX, mPosition.mY, mPosition.mZ);
}

void CCharacter::Render() {
	mpModel->Render(mMatrix);
}

void CCharacter::Collision(CCollider *m, CCollider *y) {

}