#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include "CVector.h"

class CTransform {
public:
	CVector mPosition;
	CVector mRotation;
	CVector mScale;
	CMatrix mMatrix; //�����s��
	CMatrix mMatrixTranslate; //���s�ړ��s��
	CMatrix mMatrixRotate; //��]�s��
	CMatrix mMatrixScale; //�g��k���s��
	//
	void Update();
};

#endif
