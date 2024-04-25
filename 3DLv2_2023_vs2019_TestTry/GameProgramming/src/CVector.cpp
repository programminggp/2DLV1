#include "CVector.h"
#include <math.h>
#include "Maths.h"

const CVector CVector::zero(0.0f, 0.0f, 0.0f);
const CVector CVector::one(1.0f, 1.0f, 1.0f);
const CVector CVector::left(1.0f, 0.0f, 0.0f);
const CVector CVector::right(-1.0f, 0.0f, 0.0f);
const CVector CVector::up(0.0f, 1.0f, 0.0f);
const CVector CVector::down(0.0f, -1.0f, 0.0f);
const CVector CVector::forward(0.0f, 0.0f, 1.0f);
const CVector CVector::back(0.0f, 0.0f, -1.0f);

const CVector2 CVector2::zero(0.0f, 0.0f);
const CVector2 CVector2::one(1.0f, 1.0f);
const CVector2 CVector2::left(1.0f, 0.0f);
const CVector2 CVector2::right(-1.0f, 0.0f);
const CVector2 CVector2::up(0.0f, 1.0f);
const CVector2 CVector2::down(0.0f, -1.0f);

//------------------------------
// 3次元ベクトル
//------------------------------

// コンストラクタ（引数なし）
CVector::CVector()
	: CVector(0.0f, 0.0f, 0.0f)
{
}

// コンストラクタ（xyz）
CVector::CVector(float x, float y, float z)
	: mX(x), mY(y), mZ(z)
{
}

// コンストラクタ（CVector2）
CVector::CVector(const CVector2& v)
	: CVector(v.X(), v.Y(), 0.0f)
{
}

// コンストラクタ（CVector2 + z）
CVector::CVector(const CVector2& v, float z)
	: CVector(v.X(), v.Y(), z)
{
}

// コンストラクタ（CVector4）
CVector::CVector(const CVector4& v)
	: CVector(v.X(), v.Y(), v.Z())
{
}

// デストラクタ
CVector::~CVector()
{
}

// CVector == CVector の結果を返す
bool CVector::operator==(const CVector& v) const
{
	return (mX == v.mX && mY == v.mY && mZ == v.mZ);
}

// CVector != CVector の結果を返す
bool CVector::operator!=(const CVector& v) const
{
	return (mX != v.mX || mY != v.mY || mZ != v.mZ);
}

// -CVector の演算結果を返す
CVector CVector::operator-() const
{
	return CVector(-mX, -mY, -mZ);
}

// CVector + CVector の演算結果を返す
CVector CVector::operator+(const CVector& v) const
{
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

// CVector += CVector で演算結果を自身に代入
void CVector::operator+=(const CVector& v)
{
	mX += v.mX;
	mY += v.mY;
	mZ += v.mZ;
}

// CVector - CVector の演算結果を返す
CVector CVector::operator-(const CVector& v) const
{
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

// CVector -= CVector で演算結果を自身に代入
void CVector::operator-=(const CVector& v)
{
	mX -= v.mX;
	mY -= v.mY;
	mZ -= v.mZ;
}

// CVector * float の演算結果を返す
CVector CVector::operator*(const float& f) const
{
	return CVector(mX * f, mY * f, mZ * f);
}

// CVector *= float で演算結果を自身に代入
void CVector::operator*=(const float& f)
{
	mX *= f;
	mY *= f;
	mZ *= f;
}

// CVector * CMatrixの結果をCVectorで返す
CVector CVector::operator*(const CMatrix& m) const
{
	//掛け算の結果をCVector型の値で返す
	return CVector
	(
		mX * m.M(0, 0) + mY * m.M(1, 0) + mZ * m.M(2, 0) + m.M(3, 0),
		mX * m.M(0, 1) + mY * m.M(1, 1) + mZ * m.M(2, 1) + m.M(3, 1),
		mX * m.M(0, 2) + mY * m.M(1, 2) + mZ * m.M(2, 2) + m.M(3, 2)
	);
}

// 各軸の値を設定
void CVector::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

// X軸の値を取得
float CVector::X() const
{
	return mX;
}

// X軸の値を設定
void CVector::X(float x)
{
	mX = x;
}

// Y軸の値を取得
float CVector::Y() const
{
	return mY;
}

// Y軸の値を設定
void CVector::Y(float y)
{
	mY = y;
}

// Z軸の値を取得
float CVector::Z() const
{
	return mZ;
}

// Z軸の値を設定
void CVector::Z(float z)
{
	mZ = z;
}

// ベクトルを正規化
void CVector::Normalize()
{
	float length = Length();
	if (length == 0.0f) return;
	*this *= (1.0f / length);
}

// 正規化したベクトルを取得
CVector CVector::Normalized() const
{
	float length = Length();
	if (length == 0.0f) return *this;
	return *this * (1.0f / length);
}

// 指定したベクトルとの内積を求める
float CVector::Dot(const CVector& v) const
{
	return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

// 2つのベクトルの内積を求める
float CVector::Dot(const CVector& v0, const CVector& v1)
{
	return v0.mX * v1.mX + v0.mY * v1.mY + v0.mZ * v1.mZ;
}

// 指定したベクトルとの外積を求める
CVector CVector::Cross(const CVector& v) const
{
	return CVector
	(
		mY * v.mZ - mZ * v.mY,
		mZ * v.mX - mX * v.mZ,
		mX * v.mY - mY * v.mX
	);
}

// 2つのベクトルの外積を求める
CVector CVector::Cross(const CVector& v0, const CVector& v1)
{
	return CVector
	(
		v0.mY * v1.mZ - v0.mZ * v1.mY,
		v0.mZ * v1.mX - v0.mX * v1.mZ,
		v0.mX * v1.mY - v0.mY * v1.mX
	);
}

// ベクトルの長さを取得
float CVector::Length() const
{
	// sqrt関数で平方根を返す
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}

// ベクトルの2乗の長さを取得
float CVector::LengthSqr() const
{
	// sqrt関数を使用しない分高速
	return mX * mX + mY * mY + mZ * mZ;
}

// 2点間の距離を求める
float CVector::Distance(const CVector& p0, const CVector& p1)
{
	return (p0 - p1).Length();
}

// 2つのベクトルの角度を求める
float CVector::Angle(const CVector& v0, const CVector& v1)
{
	float length = v0.Length() * v1.Length();
	if (length == 0.0f) return 0.0f;
	return acosf(Dot(v0, v1) / length);
}

// 2点間を線形補間する
CVector CVector::Lerp(const CVector& a, const CVector& b, float t)
{
	t = Math::Clamp01(t);
	return a + (b - a) * t;
}

// 2つのベクトル間を球面線形補間する
CVector CVector::Slerp(const CVector& a, const CVector& b, float t)
{
	t = Math::Clamp01(t);
	CVector v0 = a.Normalized();
	CVector v1 = b.Normalized();

	float d = Math::Clamp(CVector::Dot(v0, v1), -1.0f, 1.0f);
	float theta = acosf(d);
	float sinTheta = sinf(theta);
	if (sinTheta == 0.0f) return v1;

	float from = sinf(theta * (1.0f - t));
	float to = sinf(theta * t);

	//float lengthLerp = Math::Lerp(a.Length(), b.Length(), t);
	CVector v = (v0 * from + v1 * to) * (1.0f / sinTheta);
	return v.Normalized();

	//float d = Math::Clamp01(CVector::Dot(v0, v1));
	//float angle = acosf(d);
	//float sinth = sinf(angle);
	//if (sinth == 0.0f) return v1;

	//float p1 = sinf(angle * (1.0f - t));
	//float p2 = sinf(angle * t);

	//CVector ret = (v0 * p1 + v1 * p2) * (1.0f / sinth);
	//return ret.Normalized();
}

//------------------------------
// 2次元ベクトル
//------------------------------

// コンストラクタ（引数なし）
CVector2::CVector2()
	: CVector2(0.0f, 0.0f)
{
}

// コンストラクタ（xy）
CVector2::CVector2(float x, float y)
	: mX(x), mY(y)
{
}

// コンストラクタ（CVector）
CVector2::CVector2(const CVector& v)
	: CVector2(v.X(), v.Y())
{
}

// デストラクタ
CVector2::~CVector2()
{
}

// CVector2 == CVector2 の結果を返す
bool CVector2::operator==(const CVector2& v) const
{
	return (mX == v.mX && mY == v.mY);
}

// CVector2 != CVector2 の結果を返す
bool CVector2::operator!=(const CVector2& v) const
{
	return (mX != v.mX || mY != v.mY);
}

// -CVector2 の演算結果を返す
CVector2 CVector2::operator-() const
{
	return CVector2(-mX, -mY);
}

// CVector2 + CVector2 の演算結果を返す
CVector2 CVector2::operator+(const CVector2& v) const
{
	return CVector2(mX + v.mX, mY + v.mY);
}

// CVector2 += CVector2 で演算結果を自身に代入
void CVector2::operator+=(const CVector2& v)
{
	mX += v.mX;
	mY += v.mY;
}

// CVector2 - CVector2 の演算結果を返す
CVector2 CVector2::operator-(const CVector2& v) const
{
	return CVector2(mX - v.mX, mY - v.mY);
}

// CVector2 -= CVector2 で演算結果を自身に代入
void CVector2::operator-=(const CVector2& v)
{
	mX -= v.mX;
	mY -= v.mY;
}

// CVector2 * float の演算結果を返す
CVector2 CVector2::operator*(const float& f) const
{
	return CVector2(mX * f, mY * f);
}

// CVector2 *= float で演算結果を自身に代入
void CVector2::operator*=(const float& f)
{
	mX *= f;
	mY *= f;
}

//// CVector2 * CMatrixの結果をCVector2で返す
//CVector CVector::operator*(const CMatrix& m)
//{
//	//掛け算の結果をCVector型の値で返す
//	return CVector
//	(
//		mX * m.M(0, 0) + mY * m.M(1, 0) + mZ * m.M(2, 0) + m.M(3, 0),
//		mX * m.M(0, 1) + mY * m.M(1, 1) + mZ * m.M(2, 1) + m.M(3, 1),
//		mX * m.M(0, 2) + mY * m.M(1, 2) + mZ * m.M(2, 2) + m.M(3, 2)
//	);
//}

// 各軸の値を設定
void CVector2::Set(float x, float y)
{
	mX = x;
	mY = y;
}

// X軸の値を取得
float CVector2::X() const
{
	return mX;
}

// X軸の値を設定
void CVector2::X(float x)
{
	mX = x;
}

// Y軸の値を取得
float CVector2::Y() const
{
	return mY;
}

// Y軸の値を設定
void CVector2::Y(float y)
{
	mY = y;
}

// ベクトルを正規化
void CVector2::Normalize()
{
	float length = Length();
	if (length == 0.0f) return;
	*this *= (1.0f / length);
}

// 正規化したベクトルを取得
CVector2 CVector2::Normalized() const
{
	float length = Length();
	if (length == 0.0f) return *this;
	return *this * (1.0f / length);
}

// 指定したベクトルとの内積を求める
float CVector2::Dot(const CVector2& v) const
{
	return mX * v.mX + mY * v.mY;
}

// 2つのベクトルの内積を求める
float CVector2::Dot(const CVector2& v0, const CVector2& v1)
{
	return v0.mX * v1.mX + v0.mY * v1.mY;
}

// 指定したベクトルとの外積を求める
float CVector2::Cross(const CVector2& v) const
{
	return mX * v.mY - mY * v.mX;
}

// 2つのベクトルの外積を求める
float CVector2::Cross(const CVector2& v0, const CVector2& v1)
{
	return v0.mX * v1.mY - v0.mY * v1.mX;
}

// ベクトルの長さを取得
float CVector2::Length() const
{
	// sqrt関数で平方根を返す
	return sqrtf(mX * mX + mY * mY);
}

// ベクトルの2乗の長さを取得
float CVector2::LengthSqr() const
{
	// sqrt関数を使用しない分高速
	return mX * mX + mY * mY;
}

// 2点間の距離を求める
float CVector2::Distance(const CVector2& p0, const CVector2& p1)
{
	return (p0 - p1).Length();
}

// 2つのベクトルの角度を求める
float CVector2::Angle(const CVector2& v0, const CVector2& v1)
{
	float length = v0.Length() * v1.Length();
	if (length == 0.0f) return 0.0f;
	return acosf(Dot(v0, v1) / length);
}

//------------------------------
// CVector4
//------------------------------

// コンストラクタ（引数なし）
CVector4::CVector4()
	: CVector4(0.0f, 0.0f, 0.0f, 0.0f)
{
}

// コンストラクタ（xyzw）
CVector4::CVector4(float x, float y, float z, float w)
	: mX(x), mY(y), mZ(z), mW(w)
{
}

// コンストラクタ（xyz）
CVector4::CVector4(float x, float y, float z)
	: CVector4(x, y, z, 0.0f)
{
}

// コンストラクタ（CVector）
CVector4::CVector4(const CVector& v)
	: CVector4(v.X(), v.Y(), v.Z())
{
}

// コンストラクタ（CVector）
CVector4::CVector4(const CVector& v, float w)
	: CVector4(v.X(), v.Y(), v.Z(), w)
{
}

//Set(X座標, Y座標, Z座標, W)
void CVector4::Set(float x, float y, float z, float w)
{
	mX = x;
	mY = y;
	mZ = z;
	mW = w;
}

//Set(X座標, Y座標, Z座標)
void CVector4::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

float CVector4::X() const
{
	return mX;
}

void CVector4::X(float x)
{
	mX = x;
}

float CVector4::Y() const
{
	return mY;
}

void CVector4::Y(float y)
{
	mY = y;
}

float CVector4::Z() const
{
	return mZ;
}

void CVector4::Z(float z)
{
	mZ = z;
}

float CVector4::W() const
{
	return mW;
}

void CVector4::W(float w)
{
	mW = w;
}

float CVector4::V(int n) const
{
	if (n == 0) return mX;
	if (n == 1) return mY;
	if (n == 2) return mZ;
	return mW;
}

void CVector4::V(int n, float v)
{
	if (n == 0) mX = v;
	else if (n == 1) mY = v;
	else if (n == 2) mZ = v;
	else mW = v;
}

void CVector4::operator=(const CVector& v)
{
	mX = v.X();
	mY = v.Y();
	mZ = v.Z();
}

bool CVector4::operator==(const CVector4& v) const
{
	return mX == v.mX && mY == v.mY && mZ == v.mZ && mW != v.mW;
}

bool CVector4::operator!=(const CVector4& v) const
{
	return mX != v.mX || mY != v.mY && mZ != v.mZ && mW != v.mW;
}

CVector4 CVector4::operator+(const CVector4& v) const
{
	return CVector4(mX + v.mX, mY + v.mY, mZ + v.mZ, mW + v.mW);
}

void CVector4::operator+=(const CVector4& v)
{
	mX += v.mX;
	mY += v.mY;
	mZ += v.mZ;
	mW += v.mW;
}

CVector4 CVector4::operator-(const CVector4& v) const
{
	return CVector4(mX - v.mX, mY - v.mY, mZ - v.mZ, mW - v.mW);
}

void CVector4::operator-=(const CVector4& v)
{
	mX -= v.mX;
	mY -= v.mY;
	mZ -= v.mZ;
	mW -= v.mW;
}

CVector4 CVector4::operator*(const float& f) const
{
	return CVector4(mX * f, mY * f, mZ * f, mW * f);
}

void CVector4::operator*=(const float& f)
{
	mX *= f;
	mY *= f;
	mZ *= f;
	mW *= f;
}

CVector4 CVector4::operator*(const CMatrix& m) const
{
	CVector4 ret;
	for (int i = 0; i < 4; i++)
	{
		float v = 0.0f;
		for (int j = 0; j < 4; j++)
		{
			v += m.M(j, i) * V(j);
		}
		ret.V(i, v);
	}
	return ret;
}

//CMatrix * CVector の演算結果を返す
CVector operator*(const CMatrix& m, const CVector& v)
{
	return v * m;
}

//CMatrix * CVector4 の演算結果を返す
CVector4 operator*(const CMatrix& m, const CVector4& v)
{
	return v * m;
}
