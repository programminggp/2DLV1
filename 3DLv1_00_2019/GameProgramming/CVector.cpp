#include "CVector.h"
/*
//コンストラクタ
//各値を0に初期化
CVector::CVector()
: mX(0.0f), mY(0.0f), mZ(0.0f) {}
*/

//Set(X座標, Y座標, Z座標)
void CVector::Set(float x, float y, float z) {
	//各軸の値を代入します
	mX = x;
	mY = y;
	mZ = z;
}

//行列との掛け算
//Multi(行列)
CVector CVector::Multi(const CMatrix &m) {
	CVector v;
	v.mX = mX * m.mM[0][0] + mY * m.mM[1][0] + mZ * m.mM[2][0] + m.mM[3][0];
	v.mY = mX * m.mM[0][1] + mY * m.mM[1][1] + mZ * m.mM[2][1] + m.mM[3][1];
	v.mZ = mX * m.mM[0][2] + mY * m.mM[1][2] + mZ * m.mM[2][2] + m.mM[3][2];
	return v;
}

