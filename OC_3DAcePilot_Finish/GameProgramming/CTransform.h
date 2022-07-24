#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include "CVector.h"

class CTransform {
public:
	CVector mPosition;
	CVector mRotation;
	CVector mScale;
	CMatrix mMatrix; //合成行列
	CMatrix mMatrixTranslate; //平行移動行列
	CMatrix mMatrixRotate; //回転行列
	CMatrix mMatrixScale; //拡大縮小行列
	//
	void Update();
};

#endif
