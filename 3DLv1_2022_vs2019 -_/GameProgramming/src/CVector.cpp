#include "CVector.h"
#include"CMatrix.h"
#include <math.h>

CVector::CVector()
	:mX(0.0f), mY(0.0f), mZ(0.0f)
{
}

CVector CVector::Normalize() const {
	//�x�N�g���̑傫���Ŋ������x�N�g����Ԃ�(�����P�̃x�N�g��)
	return *this * (1.0f / Length());
}

//�O��
CVector CVector::Cross(const CVector& v) const
{
	 return CVector(mY * v.mZ - mZ * v.mY, mZ * v.mX - mX * v.mZ, mX * v.mY - mY * v.mX);
}

//*���Z�q�̃I�[�o�[���[�h
CVector CVector::operator*(const float& f) const
{
	return CVector(mX * f, mY * f, mZ * f);
}

//����
float CVector::Dot(const CVector& v)const {
	return mX * v.mX + mY * v.mY + mZ * v.mZ;
}

//�x�N�g���̒�����Ԃ�
float CVector::Length() const
{
	//sqrt�֐��ŕ�������Ԃ�
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}

//Set(X���W,Y���W,Z���W)
void CVector::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

CVector::CVector(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

float CVector::X() const
{
	return mX;
}

float CVector::Y() const
{
	return mY;
}

float CVector::Z() const
{
	return mZ;
}

//+���Z�q�̃I�[�o�[���[�h
//CVector + CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator+(const CVector& v)const
{
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}
//-���Z�q�̃I�[�o�[���[�h
//CVector - CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator-(const CVector& v)const
{
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

CVector CVector::operator*(const CMatrix &m)
{
	//�|���Z�̌��ʂ�CVector�^�̒l�ŕԂ�
	return CVector(
		mX * m.M(0, 0) + mY * m.M(1, 0) + mZ * m.M(2, 0) + m.M(3, 0),
		mX * m.M(0, 1) + mY * m.M(1, 1) + mZ * m.M(2, 1) + m.M(3, 1),
		mX * m.M(0, 2) + mY * m.M(1, 2) + mZ * m.M(2, 2) + m.M(3, 2)
	);
}
