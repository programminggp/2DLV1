#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include "CVector.h"
/*
トランスフォームクラス
位置、回転、拡縮、変換行列の基本クラス
*/
class CTransform {
public:
	CVector mPosition;	//位置
	CVector mRotation;	//回転
	CVector mScale;	//拡大縮小
	CMatrix mMatrixTranslate; //平行移動行列
	CMatrix mMatrixRotate; //回転行列
	CMatrix mMatrixScale; //拡大縮小行列
	CMatrix mMatrix; //合成行列
	//行列更新処理
	void Update();
};

#endif
