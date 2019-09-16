#ifndef CVECTOR_H
#define CVECTOR_H
//CMatrixクラスのインクルード
#include "CMatrix.h"
/*
 ベクトルクラス
 ベクトルデータを扱います
*/
class CVector {
public:
	//3D各軸での値を設定
	float mX, mY, mZ;
	//各軸での値の設定
	//Set(X座標, Y座標, Z座標)
	void Set(float x, float y, float z);
	//行列との掛け算
	//Multi(行列)
	CVector Multi(const CMatrix &m);
	//デフォルトコンストラクタ
	CVector();
	//コンストラクタ
	//CVector(X座標, Y座標, Z座標)
	CVector(float x, float y, float z);
	//*演算子のオーバーロード
	//CVector * CMatrix の演算結果を返す
	CVector operator*(const CMatrix &m);
};

#endif
