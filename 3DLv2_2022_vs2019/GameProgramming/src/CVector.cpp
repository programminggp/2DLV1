#include "CVector.h"
//
#define  _USE_MATH_DEFINES
#include <math.h>

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

//Set(X���W, Y���W, Z���W)
void CVector::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}
void CVector::Set(const CVector& v)
{
	*this = v;
	//mX = v.mX;
	//mY = v.mY;
	//mZ = v.mZ;
}
//�f�t�H���g�R���X�g���N�^
CVector::CVector()
: mX(0.0f), mY(0.0f), mZ(0.0f)
{}
//�R���X�g���N�^
//CVector(X���W, Y���W, Z���W)
CVector::CVector(float x, float y, float z)
{
	Set(x, y, z);
}

//CVector * CMatrix�̌��ʂ�CVector�ŕԂ�
CVector CVector::operator*(const CMatrix &m) const
{
	//�|���Z�̌��ʂ�CVector�^�̒l�ŕԂ�
	return CVector(
		mX * m.M(0,0) + mY * m.M(1,0) + mZ * m.M(2,0) + m.M(3,0),
		mX * m.M(0,1) + mY * m.M(1,1) + mZ * m.M(2,1) + m.M(3,1),
		mX * m.M(0,2) + mY * m.M(1,2) + mZ * m.M(2,2) + m.M(3,2)
		);
}

//-���Z�q�̃I�[�o�[���[�h
//CVector - CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator-(const CVector &v) const
{
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

//�x�N�g���̒�����Ԃ�
float CVector::Length() const {
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}
//����
float CVector::Dot(const CVector &v) const 
{
	return mX*v.mX + mY*v.mY + mZ * v.mZ;
}

CVector CVector::Normalize() const 
{
	//�x�N�g���̑傫���Ŋ������x�N�g����Ԃ��i����1�̃x�N�g���j
	return *this * (1.0f / Length());
}
//�O��
CVector CVector::Cross(const CVector &v) const 
{
	return CVector(mY*v.mZ - mZ*v.mY, mZ*v.mX - mX*v.mZ, mX*v.mY - mY*v.mX);
}
//*���Z�q�̃I�[�o�[���[�h
//CVector * float �̉��Z���ʂ�Ԃ�
CVector CVector::operator*(const float &f) const 
{
	return CVector(mX * f, mY * f, mZ * f);
}
//+���Z�q�̃I�[�o�[���[�h
//CVector + CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator+(const CVector &v) const
{
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

//Y���ł̉�]�p�x�̎擾
//�x�x��Ԃ��iZ���{��0�x�j
float CVector::GetRotationY() const
{
	//���W�A�������ɕϊ����ĕԂ�
	return (float)(atan2(mX,mZ) * 180.0f / M_PI);
}

//X���ł̉�]�p�x�̎擾
//�x�x��Ԃ��iZ���{��0�x�j
//GetRotationX(Y������)
float CVector::GetRotationX(CVector& ay) const
{
	CVector z = this->Normalize();
	CVector y = ay.Normalize();
	double rad = 0.0f;

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
	return (float)(rad * -180.0f / M_PI);
}
