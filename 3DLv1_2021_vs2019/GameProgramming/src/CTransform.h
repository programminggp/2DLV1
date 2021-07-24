#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include "CVector.h"
/*
�g�����X�t�H�[���N���X
�ʒu�A��]�A�g�k�A�ϊ��s��̊�{�N���X
*/
class CTransform {
protected: //�q�N���X�̓A�N�Z�X�\
	CVector mPosition;	//�ʒu
	CVector mRotation;	//��]
	CVector mScale;	//�g��k��
	CMatrix mMatrixTranslate; //���s�ړ��s��
	CMatrix mMatrixRotate; //��]�s��
	CMatrix mMatrixScale; //�g��k���s��
	CMatrix mMatrix; //�����s��
public:
	const CVector& Position() const;
	void Position(const CVector& v);
	void Rotation(const CVector& v);
	void Scale(const CVector& v);
	const CMatrix& Matrix() const;
	const CMatrix& MatrixRotate() const;
	//�s��X�V����
	void Update();
};

#endif
