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
// 3�����x�N�g��
//------------------------------

// �R���X�g���N�^�i�����Ȃ��j
CVector::CVector()
	: CVector(0.0f, 0.0f, 0.0f)
{
}

// �R���X�g���N�^�ixyz�j
CVector::CVector(float x, float y, float z)
	: mX(x), mY(y), mZ(z)
{
}

// �R���X�g���N�^�iCVector2�j
CVector::CVector(const CVector2& v)
	: CVector(v.X(), v.Y(), 0.0f)
{
}

// �R���X�g���N�^�iCVector2 + z�j
CVector::CVector(const CVector2& v, float z)
	: CVector(v.X(), v.Y(), z)
{
}

// �R���X�g���N�^�iCVector4�j
CVector::CVector(const CVector4& v)
	: CVector(v.X(), v.Y(), v.Z())
{
}

// �f�X�g���N�^
CVector::~CVector()
{
}

// CVector == CVector �̌��ʂ�Ԃ�
bool CVector::operator==(const CVector& v) const
{
	return (mX == v.mX && mY == v.mY && mZ == v.mZ);
}

// CVector != CVector �̌��ʂ�Ԃ�
bool CVector::operator!=(const CVector& v) const
{
	return (mX != v.mX || mY != v.mY || mZ != v.mZ);
}

// -CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator-() const
{
	return CVector(-mX, -mY, -mZ);
}

// CVector + CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator+(const CVector& v) const
{
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

// CVector += CVector �ŉ��Z���ʂ����g�ɑ��
void CVector::operator+=(const CVector& v)
{
	mX += v.mX;
	mY += v.mY;
	mZ += v.mZ;
}

// CVector - CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator-(const CVector& v) const
{
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

// CVector -= CVector �ŉ��Z���ʂ����g�ɑ��
void CVector::operator-=(const CVector& v)
{
	mX -= v.mX;
	mY -= v.mY;
	mZ -= v.mZ;
}

// CVector * float �̉��Z���ʂ�Ԃ�
CVector CVector::operator*(const float& f) const
{
	return CVector(mX * f, mY * f, mZ * f);
}

// CVector *= float �ŉ��Z���ʂ����g�ɑ��
void CVector::operator*=(const float& f)
{
	mX *= f;
	mY *= f;
	mZ *= f;
}

// CVector * CMatrix�̌��ʂ�CVector�ŕԂ�
CVector CVector::operator*(const CMatrix& m) const
{
	//�|���Z�̌��ʂ�CVector�^�̒l�ŕԂ�
	return CVector
	(
		mX * m.M(0, 0) + mY * m.M(1, 0) + mZ * m.M(2, 0) + m.M(3, 0),
		mX * m.M(0, 1) + mY * m.M(1, 1) + mZ * m.M(2, 1) + m.M(3, 1),
		mX * m.M(0, 2) + mY * m.M(1, 2) + mZ * m.M(2, 2) + m.M(3, 2)
	);
}

// �e���̒l��ݒ�
void CVector::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

// X���̒l���擾
float CVector::X() const
{
	return mX;
}

// X���̒l��ݒ�
void CVector::X(float x)
{
	mX = x;
}

// Y���̒l���擾
float CVector::Y() const
{
	return mY;
}

// Y���̒l��ݒ�
void CVector::Y(float y)
{
	mY = y;
}

// Z���̒l���擾
float CVector::Z() const
{
	return mZ;
}

// Z���̒l��ݒ�
void CVector::Z(float z)
{
	mZ = z;
}

// �x�N�g���𐳋K��
void CVector::Normalize()
{
	float length = Length();
	if (length == 0.0f) return;
	*this *= (1.0f / length);
}

// ���K�������x�N�g�����擾
CVector CVector::Normalized() const
{
	float length = Length();
	if (length == 0.0f) return *this;
	return *this * (1.0f / length);
}

// �w�肵���x�N�g���Ƃ̓��ς����߂�
float CVector::Dot(const CVector& v) const
{
	return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

// 2�̃x�N�g���̓��ς����߂�
float CVector::Dot(const CVector& v0, const CVector& v1)
{
	return v0.mX * v1.mX + v0.mY * v1.mY + v0.mZ * v1.mZ;
}

// �w�肵���x�N�g���Ƃ̊O�ς����߂�
CVector CVector::Cross(const CVector& v) const
{
	return CVector
	(
		mY * v.mZ - mZ * v.mY,
		mZ * v.mX - mX * v.mZ,
		mX * v.mY - mY * v.mX
	);
}

// 2�̃x�N�g���̊O�ς����߂�
CVector CVector::Cross(const CVector& v0, const CVector& v1)
{
	return CVector
	(
		v0.mY * v1.mZ - v0.mZ * v1.mY,
		v0.mZ * v1.mX - v0.mX * v1.mZ,
		v0.mX * v1.mY - v0.mY * v1.mX
	);
}

// �x�N�g���̒������擾
float CVector::Length() const
{
	// sqrt�֐��ŕ�������Ԃ�
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}

// �x�N�g����2��̒������擾
float CVector::LengthSqr() const
{
	// sqrt�֐����g�p���Ȃ�������
	return mX * mX + mY * mY + mZ * mZ;
}

// 2�_�Ԃ̋��������߂�
float CVector::Distance(const CVector& p0, const CVector& p1)
{
	return (p0 - p1).Length();
}

// 2�̃x�N�g���̊p�x�����߂�
float CVector::Angle(const CVector& v0, const CVector& v1)
{
	float length = v0.Length() * v1.Length();
	if (length == 0.0f) return 0.0f;
	return acosf(Dot(v0, v1) / length);
}

// 2�_�Ԃ���`��Ԃ���
CVector CVector::Lerp(const CVector& a, const CVector& b, float t)
{
	t = Math::Clamp01(t);
	return a + (b - a) * t;
}

// 2�̃x�N�g���Ԃ����ʐ��`��Ԃ���
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
// 2�����x�N�g��
//------------------------------

// �R���X�g���N�^�i�����Ȃ��j
CVector2::CVector2()
	: CVector2(0.0f, 0.0f)
{
}

// �R���X�g���N�^�ixy�j
CVector2::CVector2(float x, float y)
	: mX(x), mY(y)
{
}

// �R���X�g���N�^�iCVector�j
CVector2::CVector2(const CVector& v)
	: CVector2(v.X(), v.Y())
{
}

// �f�X�g���N�^
CVector2::~CVector2()
{
}

// CVector2 == CVector2 �̌��ʂ�Ԃ�
bool CVector2::operator==(const CVector2& v) const
{
	return (mX == v.mX && mY == v.mY);
}

// CVector2 != CVector2 �̌��ʂ�Ԃ�
bool CVector2::operator!=(const CVector2& v) const
{
	return (mX != v.mX || mY != v.mY);
}

// -CVector2 �̉��Z���ʂ�Ԃ�
CVector2 CVector2::operator-() const
{
	return CVector2(-mX, -mY);
}

// CVector2 + CVector2 �̉��Z���ʂ�Ԃ�
CVector2 CVector2::operator+(const CVector2& v) const
{
	return CVector2(mX + v.mX, mY + v.mY);
}

// CVector2 += CVector2 �ŉ��Z���ʂ����g�ɑ��
void CVector2::operator+=(const CVector2& v)
{
	mX += v.mX;
	mY += v.mY;
}

// CVector2 - CVector2 �̉��Z���ʂ�Ԃ�
CVector2 CVector2::operator-(const CVector2& v) const
{
	return CVector2(mX - v.mX, mY - v.mY);
}

// CVector2 -= CVector2 �ŉ��Z���ʂ����g�ɑ��
void CVector2::operator-=(const CVector2& v)
{
	mX -= v.mX;
	mY -= v.mY;
}

// CVector2 * float �̉��Z���ʂ�Ԃ�
CVector2 CVector2::operator*(const float& f) const
{
	return CVector2(mX * f, mY * f);
}

// CVector2 *= float �ŉ��Z���ʂ����g�ɑ��
void CVector2::operator*=(const float& f)
{
	mX *= f;
	mY *= f;
}

//// CVector2 * CMatrix�̌��ʂ�CVector2�ŕԂ�
//CVector CVector::operator*(const CMatrix& m)
//{
//	//�|���Z�̌��ʂ�CVector�^�̒l�ŕԂ�
//	return CVector
//	(
//		mX * m.M(0, 0) + mY * m.M(1, 0) + mZ * m.M(2, 0) + m.M(3, 0),
//		mX * m.M(0, 1) + mY * m.M(1, 1) + mZ * m.M(2, 1) + m.M(3, 1),
//		mX * m.M(0, 2) + mY * m.M(1, 2) + mZ * m.M(2, 2) + m.M(3, 2)
//	);
//}

// �e���̒l��ݒ�
void CVector2::Set(float x, float y)
{
	mX = x;
	mY = y;
}

// X���̒l���擾
float CVector2::X() const
{
	return mX;
}

// X���̒l��ݒ�
void CVector2::X(float x)
{
	mX = x;
}

// Y���̒l���擾
float CVector2::Y() const
{
	return mY;
}

// Y���̒l��ݒ�
void CVector2::Y(float y)
{
	mY = y;
}

// �x�N�g���𐳋K��
void CVector2::Normalize()
{
	float length = Length();
	if (length == 0.0f) return;
	*this *= (1.0f / length);
}

// ���K�������x�N�g�����擾
CVector2 CVector2::Normalized() const
{
	float length = Length();
	if (length == 0.0f) return *this;
	return *this * (1.0f / length);
}

// �w�肵���x�N�g���Ƃ̓��ς����߂�
float CVector2::Dot(const CVector2& v) const
{
	return mX * v.mX + mY * v.mY;
}

// 2�̃x�N�g���̓��ς����߂�
float CVector2::Dot(const CVector2& v0, const CVector2& v1)
{
	return v0.mX * v1.mX + v0.mY * v1.mY;
}

// �w�肵���x�N�g���Ƃ̊O�ς����߂�
float CVector2::Cross(const CVector2& v) const
{
	return mX * v.mY - mY * v.mX;
}

// 2�̃x�N�g���̊O�ς����߂�
float CVector2::Cross(const CVector2& v0, const CVector2& v1)
{
	return v0.mX * v1.mY - v0.mY * v1.mX;
}

// �x�N�g���̒������擾
float CVector2::Length() const
{
	// sqrt�֐��ŕ�������Ԃ�
	return sqrtf(mX * mX + mY * mY);
}

// �x�N�g����2��̒������擾
float CVector2::LengthSqr() const
{
	// sqrt�֐����g�p���Ȃ�������
	return mX * mX + mY * mY;
}

// 2�_�Ԃ̋��������߂�
float CVector2::Distance(const CVector2& p0, const CVector2& p1)
{
	return (p0 - p1).Length();
}

// 2�̃x�N�g���̊p�x�����߂�
float CVector2::Angle(const CVector2& v0, const CVector2& v1)
{
	float length = v0.Length() * v1.Length();
	if (length == 0.0f) return 0.0f;
	return acosf(Dot(v0, v1) / length);
}

//------------------------------
// CVector4
//------------------------------

// �R���X�g���N�^�i�����Ȃ��j
CVector4::CVector4()
	: CVector4(0.0f, 0.0f, 0.0f, 0.0f)
{
}

// �R���X�g���N�^�ixyzw�j
CVector4::CVector4(float x, float y, float z, float w)
	: mX(x), mY(y), mZ(z), mW(w)
{
}

// �R���X�g���N�^�ixyz�j
CVector4::CVector4(float x, float y, float z)
	: CVector4(x, y, z, 0.0f)
{
}

// �R���X�g���N�^�iCVector�j
CVector4::CVector4(const CVector& v)
	: CVector4(v.X(), v.Y(), v.Z())
{
}

// �R���X�g���N�^�iCVector�j
CVector4::CVector4(const CVector& v, float w)
	: CVector4(v.X(), v.Y(), v.Z(), w)
{
}

//Set(X���W, Y���W, Z���W, W)
void CVector4::Set(float x, float y, float z, float w)
{
	mX = x;
	mY = y;
	mZ = z;
	mW = w;
}

//Set(X���W, Y���W, Z���W)
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

//CMatrix * CVector �̉��Z���ʂ�Ԃ�
CVector operator*(const CMatrix& m, const CVector& v)
{
	return v * m;
}

//CMatrix * CVector4 �̉��Z���ʂ�Ԃ�
CVector4 operator*(const CMatrix& m, const CVector4& v)
{
	return v * m;
}
