#include "CVector.h"
//円周率M_PIを有効にする
#define _USE_MATH_DEFINES
#include <math.h>
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
	CVector v;	//戻り値用作成
	//1行1列目の計算
	v.mX = mX * m.mM[0][0] + mY * m.mM[1][0] + mZ * m.mM[2][0] + m.mM[3][0];
	//1行2列目の計算
	v.mY = mX * m.mM[0][1] + mY * m.mM[1][1] + mZ * m.mM[2][1] + m.mM[3][1];
	//1行3列目の計算
	v.mZ = mX * m.mM[0][2] + mY * m.mM[1][2] + mZ * m.mM[2][2] + m.mM[3][2];
	return v;//戻り値を返す
}

//デフォルトコンストラクタ
CVector::CVector()
: mX(0.0f), mY(0.0f), mZ(0.0f)
{
}
//コンストラクタ
//CVector(X座標, Y座標, Z座標)
CVector::CVector(float x, float y, float z)
: mX(x), mY(y), mZ(z)
{
}
//*演算子のオーバーロード
//CVector * CMatrix の演算結果を返す
CVector CVector::operator*(const CMatrix &m) {
	//掛け算の結果を返す
	return Multi(m);
}
//-演算しのオーバーロード
//CVector - CVector の演算結果を返す
CVector CVector::operator-(const CVector &v) {
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}
//ベクトルの長さを返す
float CVector::Length() const {
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}

//内積
float CVector::Dot(const CVector &v) {
	return mX*v.mX + mY*v.mY + mZ * v.mZ;
}

//正規化
//大きさ1のベクトルを返す
CVector CVector::Normalize() const {
	//ベクトルの大きさで割ったベクトルを返す（長さ1のベクトル）
//	return CVector(mX / Length(), mY / Length(), mZ / Length());
	return *this * (1.0f/ Length());
}
//外積
CVector CVector::Cross(const CVector &v) const {
	return CVector(mY*v.mZ - mZ*v.mY, mZ*v.mX - mX*v.mZ, mX*v.mY - mY*v.mX);
}
//*演算子のオーバーロード
//CVector * float の演算結果を返す
CVector CVector::operator*(const float &f) const {
	return CVector(mX * f, mY * f, mZ * f);
}
//+演算子のオーバーロード
//CVector + CVector の演算結果を返す
CVector CVector::operator + (const CVector &v) {
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

//ベクトルからオイラー角を求める
//foward:前向きベクトル
//up:上向きベクトル
#define DEGREE(r) (r * 180.0f / M_PI)
CVector CVector::Euler(const CVector &foward, const CVector &up)
{
	CVector f = foward.Normalize();	//前方向正規化
	CVector u = up.Normalize();		//上方向正規化
	CVector L = up.Cross(f).Normalize();	//左方向求める
	f = L.Cross(u).Normalize();	//再度前方向求める
	//各軸での角度を求める
	return CVector(DEGREE(-asin(f.mY)), DEGREE(atan2(f.mX, f.mZ)), DEGREE(atan2(L.mY, u.mY)));
}

//自ベクトルからオイラー角を求める
//up:上向きベクトル
CVector CVector::Euler(const CVector &up)
{
	CVector f = this->Normalize();	//前方向正規化
	CVector u = up.Normalize();		//上方向正規化
	CVector L = up.Cross(f).Normalize();	//左方向求める
	f = L.Cross(u).Normalize();	//再度前方向求める
	//各軸での角度を求める
	return CVector(DEGREE(-asin(f.mY)), DEGREE(atan2(f.mX, f.mZ)), DEGREE(atan2(L.mY, u.mY)));
}
