#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include "CVector.h"
/*
トランスフォームクラス
位置、回転、拡縮、変換行列の基本クラス
*/
class CTransform {
protected: //子クラスはアクセス可能
	CVector mPosition;	//位置
	CVector mRotation;	//回転
	CVector mScale;	//拡大縮小
	CMatrix mMatrixTranslate; //平行移動行列
	CMatrix mMatrixRotate; //回転行列
	CMatrix mMatrixScale; //拡大縮小行列
	CMatrix mMatrix; //合成行列
public:
	const CVector& Position() const;
	void Position(const CVector& v);
	void Rotation(const CVector& v);
	void Scale(const CVector& v);
	const CMatrix& Matrix() const;
	const CMatrix& MatrixRotate() const;
	//行列更新処理
	void Update();
};

#endif
