#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include "CVector.h"
/*
トランスフォームクラス
位置、回転、拡縮、変換行列の基本クラス
*/
class CTransform {
public:
	//位置の取得
	const CVector& Position() const;
	//位置の設定
	//Position(位置)
	void Position(const CVector& v);
	//回転値の設定
	//Rotation(回転値)
	void Rotation(const CVector& v);
	//拡大縮小の設定
	//Scale(拡大縮小)
	void Scale(const CVector& v);
	//合成行列の取得
	const CMatrix& Matrix() const;
	//回転行列の取得
	const CMatrix& MatrixRotate() const;
	//行列更新処理
	void Update();
	//Update(位置, 回転, スケール)
	void Update(const CVector& pos, const CVector& rot, const CVector& scale);
protected: //子クラスはアクセス可能
	CVector mPosition;	//位置
	CVector mRotation;	//回転
	CVector mScale;	//拡大縮小
	CMatrix mMatrixTranslate; //平行移動行列
	CMatrix mMatrixRotate; //回転行列
	CMatrix mMatrixScale; //拡大縮小行列
	CMatrix mMatrix; //合成行列
};

#endif
