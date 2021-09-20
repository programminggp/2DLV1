#include "CVector.h"
//
#include <math.h>

//Set(X���W, Y���W, Z���W)
void CVector::Set(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
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
CVector CVector::operator*(const CMatrix &m)
{
	//�|���Z�̌��ʂ�CVector�^�̒l�ŕԂ�
	return CVector(
		mX * m.mM[0][0] + mY * m.mM[1][0] + mZ * m.mM[2][0] + m.mM[3][0],
		mX * m.mM[0][1] + mY * m.mM[1][1] + mZ * m.mM[2][1] + m.mM[3][1],
		mX * m.mM[0][2] + mY * m.mM[1][2] + mZ * m.mM[2][2] + m.mM[3][2]
		);
}

//-���Z���̃I�[�o�[���[�h
//CVector - CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator-(const CVector &v) {
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

//�x�N�g���̒�����Ԃ�
float CVector::Length() {
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}
//����
float CVector::Dot(const CVector &v) {
	return mX*v.mX + mY*v.mY + mZ * v.mZ;
}

CVector CVector::Normalize() {
	//�x�N�g���̑傫���Ŋ������x�N�g����Ԃ��i����1�̃x�N�g���j
	return *this * (1.0f / Length());
}
//�O��
CVector CVector::Cross(const CVector &v) {
	return CVector(mY*v.mZ - mZ*v.mY, mZ*v.mX - mX*v.mZ, mX*v.mY - mY*v.mX);
}
//*���Z�q�̃I�[�o�[���[�h
//CVector * float �̉��Z���ʂ�Ԃ�
CVector CVector::operator*(const float &f) {
	return CVector(mX * f, mY * f, mZ * f);
}
//+���Z���̃I�[�o�[���[�h
//CVector + CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator+(const CVector &v)
{
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

void CVector::operator+=(const CVector& v)
{
	mX += v.mX;
	mY += v.mY;
	mZ += v.mZ;
}
