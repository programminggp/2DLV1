#include "CTransform.h"

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

