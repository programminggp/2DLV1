#include "CMatrix.h"
#include"CVector.h"
//�W�����o�͊֐��̃C���N���[�h
#include <stdio.h>

//�\���m�F�p
void CMatrix::Print() {
	printf("%10f %10f %10f %10f\n",
		mM[0][0], mM[0][1], mM[0][2], mM[0][3]);
	printf("%10f %10f %10f %10f\n",
		mM[1][0], mM[1][1], mM[1][2], mM[1][3]);
	printf("%10f %10f %10f %10f\n",
		mM[2][0], mM[2][1], mM[2][2], mM[2][3]);
	printf("%10f %10f %10f %10f\n",
		mM[3][0], mM[3][1], mM[3][2], mM[3][3]);
}

//�f�t�H���g�R���X�g���N�^
CMatrix::CMatrix() 
{
	Identity();
}

//�P�ʍs��̍쐬
CMatrix CMatrix::Identity()
{
	mM[0][0] = mM[0][1] = mM[0][2] = mM[0][3] = 0.0f;
	mM[1][0] = mM[1][1] = mM[1][2] = mM[1][3] = 0.0f;
	mM[2][0] = mM[2][1] = mM[2][2] = mM[2][3] = 0.0f;
	mM[3][0] = mM[3][1] = mM[3][2] = mM[3][3] = 0.0f;
	mM[0][0] = mM[1][1] = mM[2][2] = mM[3][3] = 1.0f;
	//���̍s���Ԃ�
	return *this;
}

float* CMatrix::M() const
{
	return (float*)mM[0];
}

float CMatrix::M(int row, int col) const
{
	return mM[row][col];
}

void CMatrix::M(int row, int col, float value)
{
	mM[row][col] = value;
}

//�g��k���s��̍쐬
//Scale(�{��X, �{��Y, �{��Z)
CMatrix CMatrix::Scale(float sx, float sy, float sz)
{
	//�P�ʍs��ɂ���
	Identity();
	mM[0][0] = sx;
	mM[1][1] = sy;
	mM[2][2] = sz;
	//���g��Ԃ�
	return *this;
}

//�~����M_PI��L���ɂ���
#define _USE_MATH_DEFINES
//���w�֐��̃C���N���[�h
#include <math.h>

//��]�s��iY���j�̍쐬
//RotateY(�p�x)
CMatrix CMatrix::RotateY(float degree) {
	//�p�x���烉�W�A�������߂�
	float rad = (float)(degree / 180.0f * M_PI);
	//�P�ʍs��ɂ���
	Identity();
	//Y���ŉ�]����s��̐ݒ�
	mM[0][0] = mM[2][2] = cosf(rad);
	mM[0][2] = -sinf(rad);
	mM[2][0] = -mM[0][2];
	//�s���Ԃ�
	return *this;
}

//��]�s��iZ���j�̍쐬
//RotateZ(�p�x)
CMatrix CMatrix::RotateZ(float degree)
{
	//�p�x���烉�W�A�������߂�
	float rad = (float)(degree / 180.0f * M_PI);
	//�P�ʍs��ɂ���
	Identity();
	//Y���ŉ�]����s��̐ݒ�
	mM[0][0] = mM[1][1] = cosf(rad);
	mM[0][1] = sinf(rad);
	mM[1][0] = -mM[0][1];
	//�s���Ԃ�
	return *this;
}
//��]�s��iX���j�̍쐬
//RotateX(�p�x)
CMatrix CMatrix::RotateX(float degree)
{
	//�p�x���烉�W�A�������߂�
	float rad = (float)(degree / 180.0f * M_PI);
	//�P�ʍs��ɂ���
	Identity();
	//Y���ŉ�]����s��̐ݒ�
	mM[2][2] = mM[1][1] = cosf(rad);
	mM[1][2] = sinf(rad);
	mM[2][1] = -mM[1][2];
	//�s���Ԃ�
	return *this;
}
//�ړ��s��̍쐬
//Translate(�ړ���X, �ړ���Y, �ړ���Z)
CMatrix CMatrix::Translate(float mx, float my, float mz) {
	//�P�ʍs��ɂ���
	Identity();
	//Y���ŉ�]����s��̐ݒ�
	mM[3][0] = mx;
	mM[3][1] = my;
	mM[3][2] = mz;
	//���̍s���Ԃ�
	return *this;
}
//*���Z�q�̃I�[�o�[���[�h
//CMatrix * CMatrix �̉��Z���ʂ�Ԃ�
CMatrix CMatrix::operator*(const CMatrix &m) const {
	CMatrix t;
	t.mM[0][0] = mM[0][0] * m.mM[0][0] + mM[0][1] * m.mM[1][0] + mM[0][2] * m.mM[2][0] + mM[0][3] * m.mM[3][0];
	t.mM[0][1] = mM[0][0] * m.mM[0][1] + mM[0][1] * m.mM[1][1] + mM[0][2] * m.mM[2][1] + mM[0][3] * m.mM[3][1];
	t.mM[0][2] = mM[0][0] * m.mM[0][2] + mM[0][1] * m.mM[1][2] + mM[0][2] * m.mM[2][2] + mM[0][3] * m.mM[3][2];
	t.mM[0][3] = mM[0][0] * m.mM[0][3] + mM[0][1] * m.mM[1][3] + mM[0][2] * m.mM[2][3] + mM[0][3] * m.mM[3][3];

	t.mM[1][0] = mM[1][0] * m.mM[0][0] + mM[1][1] * m.mM[1][0] + mM[1][2] * m.mM[2][0] + mM[1][3] * m.mM[3][0];
	t.mM[1][1] = mM[1][0] * m.mM[0][1] + mM[1][1] * m.mM[1][1] + mM[1][2] * m.mM[2][1] + mM[1][3] * m.mM[3][1];
	t.mM[1][2] = mM[1][0] * m.mM[0][2] + mM[1][1] * m.mM[1][2] + mM[1][2] * m.mM[2][2] + mM[1][3] * m.mM[3][2];
	t.mM[1][3] = mM[1][0] * m.mM[0][3] + mM[1][1] * m.mM[1][3] + mM[1][2] * m.mM[2][3] + mM[1][3] * m.mM[3][3];

	t.mM[2][0] = mM[2][0] * m.mM[0][0] + mM[2][1] * m.mM[1][0] + mM[2][2] * m.mM[2][0] + mM[2][3] * m.mM[3][0];
	t.mM[2][1] = mM[2][0] * m.mM[0][1] + mM[2][1] * m.mM[1][1] + mM[2][2] * m.mM[2][1] + mM[2][3] * m.mM[3][1];
	t.mM[2][2] = mM[2][0] * m.mM[0][2] + mM[2][1] * m.mM[1][2] + mM[2][2] * m.mM[2][2] + mM[2][3] * m.mM[3][2];
	t.mM[2][3] = mM[2][0] * m.mM[0][3] + mM[2][1] * m.mM[1][3] + mM[2][2] * m.mM[2][3] + mM[2][3] * m.mM[3][3];

	t.mM[3][0] = mM[3][0] * m.mM[0][0] + mM[3][1] * m.mM[1][0] + mM[3][2] * m.mM[2][0] + mM[3][3] * m.mM[3][0];
	t.mM[3][1] = mM[3][0] * m.mM[0][1] + mM[3][1] * m.mM[1][1] + mM[3][2] * m.mM[2][1] + mM[3][3] * m.mM[3][1];
	t.mM[3][2] = mM[3][0] * m.mM[0][2] + mM[3][1] * m.mM[1][2] + mM[3][2] * m.mM[2][2] + mM[3][3] * m.mM[3][2];
	t.mM[3][3] = mM[3][0] * m.mM[0][3] + mM[3][1] * m.mM[1][3] + mM[3][2] * m.mM[2][3] + mM[3][3] * m.mM[3][3];

	return t;
}

int CMatrix::Size() {
	return sizeof(mM) / sizeof(float);
}

CMatrix CMatrix::Quaternion(float x, float y, float z, float w) {
	mM[0][0] = x * x - y * y - z * z + w * w;
	mM[0][1] = 2 * x * y - 2 * w * z;
	mM[0][2] = 2 * x * z + 2 * w * y;
	mM[0][3] = 0;
	mM[1][0] = 2 * x * y + 2 * w * z;
	mM[1][1] = -x * x + y * y - z * z + w * w;
	mM[1][2] = 2 * y * z - 2 * w * x;
	mM[1][3] = 0;
	mM[2][0] = 2 * x * z - 2 * w * y;
	mM[2][1] = 2 * y * z + 2 * w * x;
	mM[2][2] = -x * x - y * y + z * z + w * w;
	mM[2][3] = 0;
	mM[3][0] = 0;
	mM[3][1] = 0;
	mM[3][2] = 0;
	mM[3][3] = 1;
	return*this;
}

CMatrix CMatrix::operator*(const float& x) {
	CMatrix f;
	f.mM[0][0] = x * mM[0][0];
	f.mM[0][1] = x * mM[0][1];
	f.mM[0][2] = x * mM[0][2];
	f.mM[0][3] = x * mM[0][3];
	f.mM[1][0] = x * mM[1][0];
	f.mM[1][1] = x * mM[1][1];
	f.mM[1][2] = x * mM[1][2];
	f.mM[1][3] = x * mM[1][3];
	f.mM[2][0] = x * mM[2][0];
	f.mM[2][1] = x * mM[2][1];
	f.mM[2][2] = x * mM[2][2];
	f.mM[2][3] = x * mM[2][3];
	f.mM[3][0] = x * mM[3][0];
	f.mM[3][1] = x * mM[3][1];
	f.mM[3][2] = x * mM[3][2];
	f.mM[3][3] = x * mM[3][3];
	return f;
}

CMatrix CMatrix::operator+(const CMatrix& m) {
	mM[0][0] = mM[0][0] + m.mM[0][0];
	mM[0][1] = mM[0][1] + m.mM[0][1];
	mM[0][2] = mM[0][2] + m.mM[0][2];
	mM[0][3] = mM[0][3] + m.mM[0][3];
	mM[1][0] = mM[1][0] + m.mM[1][0];
	mM[1][1] = mM[1][1] + m.mM[1][1];
	mM[1][2] = mM[1][2] + m.mM[1][2];
	mM[1][3] = mM[1][3] + m.mM[1][3];
	mM[2][0] = mM[2][0] + m.mM[2][0];
	mM[2][1] = mM[2][1] + m.mM[2][1];
	mM[2][2] = mM[2][2] + m.mM[2][2];
	mM[2][3] = mM[2][3] + m.mM[2][3];
	mM[3][0] = mM[3][0] + m.mM[3][0];
	mM[3][1] = mM[3][1] + m.mM[3][1];
	mM[3][2] = mM[3][2] + m.mM[3][2];
	mM[3][3] = mM[3][3] + m.mM[3][3];
	return *this;

}

void CMatrix::operator+=(const CMatrix& m) {
	mM[0][0] += m.mM[0][0];
	mM[0][1] += m.mM[0][1];
	mM[0][2] += m.mM[0][2];
	mM[0][3] += m.mM[0][3];
	mM[1][0] += m.mM[1][0];
	mM[1][1] += m.mM[1][1];
	mM[1][2] += m.mM[1][2];
	mM[1][3] += m.mM[1][3];
	mM[2][0] += m.mM[2][0];
	mM[2][1] += m.mM[2][1];
	mM[2][2] += m.mM[2][2];
	mM[2][3] += m.mM[2][3];
	mM[3][0] += m.mM[3][0];
	mM[3][1] += m.mM[3][1];
	mM[3][2] += m.mM[3][2];
	mM[3][3] += m.mM[3][3];
}

CVector CMatrix::VectorX()
{
	return CVector(mM[0][0], mM[0][1], mM[0][2]);
}

CVector CMatrix::VectorY()
{
	return CVector(mM[1][0], mM[1][1], mM[1][2]);
}

CVector CMatrix::VectorZ()
{
	return CVector(mM[2][0], mM[2][1], mM[2][2]);
}

CMatrix CMatrix::Transpose() const
{
	CMatrix t;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			t.mM[i][j] = mM[j][i];
		}
	}
	return t;
}
