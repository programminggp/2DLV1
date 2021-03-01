#include "CVector.h"
//�~����M_PI��L���ɂ���
#define _USE_MATH_DEFINES
#include <math.h>
/*
//�R���X�g���N�^
//�e�l��0�ɏ�����
CVector::CVector()
: mX(0.0f), mY(0.0f), mZ(0.0f) {}
*/

//Set(X���W, Y���W, Z���W)
void CVector::Set(float x, float y, float z) {
	//�e���̒l�������܂�
	mX = x;
	mY = y;
	mZ = z;
}

//�s��Ƃ̊|���Z
//Multi(�s��)
CVector CVector::Multi(const CMatrix &m) {
	CVector v;	//�߂�l�p�쐬
	//1�s1��ڂ̌v�Z
	v.mX = mX * m.mM[0][0] + mY * m.mM[1][0] + mZ * m.mM[2][0] + m.mM[3][0];
	//1�s2��ڂ̌v�Z
	v.mY = mX * m.mM[0][1] + mY * m.mM[1][1] + mZ * m.mM[2][1] + m.mM[3][1];
	//1�s3��ڂ̌v�Z
	v.mZ = mX * m.mM[0][2] + mY * m.mM[1][2] + mZ * m.mM[2][2] + m.mM[3][2];
	return v;//�߂�l��Ԃ�
}

//�f�t�H���g�R���X�g���N�^
CVector::CVector()
: mX(0.0f), mY(0.0f), mZ(0.0f)
{
}
//�R���X�g���N�^
//CVector(X���W, Y���W, Z���W)
CVector::CVector(float x, float y, float z)
: mX(x), mY(y), mZ(z)
{
}
//*���Z�q�̃I�[�o�[���[�h
//CVector * CMatrix �̉��Z���ʂ�Ԃ�
CVector CVector::operator*(const CMatrix &m) {
	//�|���Z�̌��ʂ�Ԃ�
	return Multi(m);
}
//-���Z���̃I�[�o�[���[�h
//CVector - CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator-(const CVector &v) {
	return CVector(mX - v.mX, mY - v.mY, mZ - v.mZ);
}
//�x�N�g���̒�����Ԃ�
float CVector::Length() const {
	return sqrtf(mX * mX + mY * mY + mZ * mZ);
}

//����
float CVector::Dot(const CVector &v) {
	return mX*v.mX + mY*v.mY + mZ * v.mZ;
}

//���K��
//�傫��1�̃x�N�g����Ԃ�
CVector CVector::Normalize() const {
	//�x�N�g���̑傫���Ŋ������x�N�g����Ԃ��i����1�̃x�N�g���j
//	return CVector(mX / Length(), mY / Length(), mZ / Length());
	return *this * (1.0f/ Length());
}
//�O��
CVector CVector::Cross(const CVector &v) const {
	return CVector(mY*v.mZ - mZ*v.mY, mZ*v.mX - mX*v.mZ, mX*v.mY - mY*v.mX);
}
//*���Z�q�̃I�[�o�[���[�h
//CVector * float �̉��Z���ʂ�Ԃ�
CVector CVector::operator*(const float &f) const {
	return CVector(mX * f, mY * f, mZ * f);
}
//+���Z�q�̃I�[�o�[���[�h
//CVector + CVector �̉��Z���ʂ�Ԃ�
CVector CVector::operator + (const CVector &v) {
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

//�x�N�g������I�C���[�p�����߂�
//foward:�O�����x�N�g��
//up:������x�N�g��
#define DEGREE(r) (r * 180.0f / M_PI)
CVector CVector::Euler(const CVector &foward, const CVector &up)
{
	CVector f = foward.Normalize();	//�O�������K��
	CVector u = up.Normalize();		//��������K��
	CVector L = up.Cross(f).Normalize();	//���������߂�
	f = L.Cross(u).Normalize();	//�ēx�O�������߂�
	//�e���ł̊p�x�����߂�
	return CVector(DEGREE(-asin(f.mY)), DEGREE(atan2(f.mX, f.mZ)), DEGREE(atan2(L.mY, u.mY)));
}

//���x�N�g������I�C���[�p�����߂�
//up:������x�N�g��
CVector CVector::Euler(const CVector &up)
{
	CVector f = this->Normalize();	//�O�������K��
	CVector u = up.Normalize();		//��������K��
	CVector L = up.Cross(f).Normalize();	//���������߂�
	f = L.Cross(u).Normalize();	//�ēx�O�������߂�
	//�e���ł̊p�x�����߂�
	return CVector(DEGREE(-asin(f.mY)), DEGREE(atan2(f.mX, f.mZ)), DEGREE(atan2(L.mY, u.mY)));
}
