#include "CTransform.h"

const CVector& CTransform::Position() const
{
	return mPosition;
}

void CTransform::Position(const CVector& v)
{
	mPosition = v;
}

const CVector& CTransform::Rotation() const
{
	return mRotation;
}

void CTransform::Rotation(const CVector& v)
{
	mRotation = v;
}

void CTransform::Scale(const CVector& v)
{
	mScale = v;
}

const CMatrix& CTransform::Matrix() const
{
	return mMatrix;
}

const CMatrix& CTransform::MatrixRotate() const
{
	return mMatrixRotate;
}

//�s��X�V����
void CTransform::Update() {
	//�g��k���s��̐ݒ�
	mMatrixScale.Scale(mScale.X(), mScale.Y(), mScale.Z());
	//��]�s��̐ݒ�
	mMatrixRotate =
		CMatrix().RotateZ(mRotation.Z()) *
		CMatrix().RotateX(mRotation.X()) *
		CMatrix().RotateY(mRotation.Y());
	//���s�ړ��s��̐ݒ�
	mMatrixTranslate.Translate(mPosition.X(), mPosition.Y(), mPosition.Z());
	//�����s��̐ݒ�
	mMatrix = mMatrixScale * mMatrixRotate * mMatrixTranslate;
}

CVector CTransform::Foward()
{
	return (CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate).Normalize();
}

