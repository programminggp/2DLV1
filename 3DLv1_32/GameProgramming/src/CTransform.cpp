#include"CTransform.h"

const CVector& CTransform::Position()const
{
	return mPosition;
}

void CTransform::Position(const CVector& v)
{
	mPosition = v;
}

void CTransform::Rotation(const CVector& v)
{
	mRotation = v;
}

void CTransform::Scale(const CVector& v)
{
	mScale = v;
}

const CMatrix& CTransform::Matrix()const 
{
	return mMatrix;
}
const CMatrix& CTransform::MatirixRotate()const
{
	return mMatrixRotate;
}

//�s��X�V����
void CTransform::Update() {
	//�g��k���s��̐ݒ�
	mMatrixScale.Scale(mScale.X(),mScale.Y(),mScale.Z());
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