#include "CVector.h"
//
#define  _USE_MATH_DEFINES
#include <math.h>

//Set(X座標, Y座標, Z座標)
void CVector::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}
//デフォルトコンストラクタ
CVector::CVector()
: mX(0.0f), mY(0.0f), mZ(0.0f)
{}
//コンストラクタ
//CVector(X座標, Y座標, Z座標)
CVector::CVector(float x, float y, float z)
{
	Set(x, y, z);
}

//CVector * CMatrixの結果をCVectorで返す
CVector CVector::operator*(const CMatrix &m)
{
	//掛け算の結果をCVector型の値で返す
	return CVector(
		mX * m.mM[0][0] + mY * m.mM[1][0] + mZ * m.mM[2][0] + m.mM[3][0],
		mX * m.mM[0][1] + mY * m.mM[1][1] + mZ * m.mM[2][1] + m.mM[3][1],
		mX * m.mM[0][2] + mY * m.mM[1][2] + mZ * m.mM[2][2] + m.mM[3][2]
		);
}

//-演算しのオーバーロード
//CVector - CVector の演算結果を返す
CVector CVector::operator-(const CVector &v) {
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

//ベクトルの長さを返す
float CVector::Length() {
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}
//内積
float CVector::Dot(const CVector &v) {
	return mX*v.mX + mY*v.mY + mZ * v.mZ;
}

CVector CVector::Normalize() {
	//ベクトルの大きさで割ったベクトルを返す（長さ1のベクトル）
	return *this * (1.0f / Length());
}
//外積
CVector CVector::Cross(const CVector &v) {
	return CVector(mY*v.mZ - mZ*v.mY, mZ*v.mX - mX*v.mZ, mX*v.mY - mY*v.mX);
}
//*演算子のオーバーロード
//CVector * float の演算結果を返す
CVector CVector::operator*(const float &f) {
	return CVector(mX * f, mY * f, mZ * f);
}
//+演算しのオーバーロード
//CVector + CVector の演算結果を返す
CVector CVector::operator+(const CVector &v)
{
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

//Y軸での回転角度の取得
//度度を返す（Z軸＋が0度）
float CVector::GetRotationY()
{
	//ラジアンを°に変換して返す
	return atan2(mX,mZ) * 180.0f / M_PI;
}

//X軸での回転角度の取得
//度度を返す（Z軸＋が0度）
//GetRotationX(Y軸方向)
float CVector::GetRotationX(CVector& ay)
{
	CVector z = this->Normalize();
	CVector y = ay.Normalize();
	float rad = 0.0f;

	if (z.mY < 0.0f)
	{
		if (y.mY < 0.0f)
		{
			rad = -M_PI - asin(z.mY);
		}
		else
		{
			rad = asin(z.mY);
		}
	}
	else
	{
		if (y.mY < 0.0f)
		{
			rad = M_PI - asin(z.mY);
		}
		else
		{
			rad = asin(z.mY);
		}
	}
	return rad * -180.0f / M_PI;
}
