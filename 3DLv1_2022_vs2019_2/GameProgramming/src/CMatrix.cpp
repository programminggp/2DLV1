#include "CMatrix.h"
//�W�����o�͊֐��̃C���N���[�h
#include <stdio.h>
//�~����M_PI��L���ɂ���
#define _USE_MATH_DEFINES
//���w�֐��̃C���N���[�h
#include <math.h>

#include "CVector.h"

//��]�s��iY���j�̍쐬
//RotateY(�p�x)
CMatrix CMatrix::RotateY(float degree) {
	//�p�x���烉�W�A�������߂�
	float rad = degree / 180.0f * M_PI;
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
	float rad = degree / 180.0f * M_PI;
	//�P�ʍs��ɂ���
	Identity();
	//Z���ŉ�]����s��̐ݒ�
	mM[0][0] = mM[1][1] = cosf(rad);
	mM[0][1] = sinf(rad);
	mM[1][0] = -mM[0][1];
	//�s���Ԃ�
	return *this;
}

CMatrix CMatrix::RotateX(float degree)
{
	//�p�x���烉�W�A�������߂�
	float rad = degree / 180.0f * M_PI;
	//�P�ʍs��ɂ���
	Identity();
	//Z���ŉ�]����s��̐ݒ�
	mM[1][1] = mM[2][2] = cosf(rad);
	mM[1][2] = sinf(rad);
	mM[2][1] = -mM[1][2];
	//�s���Ԃ�
	return *this;
}

//�ړ��s��̍쐬
//Translate(�ړ���X, �ړ���Y, �ړ���Z)
CMatrix CMatrix::Translate(float mx, float my, float mz) {
	Identity();
	mM[3][0] = mx;
	mM[3][1] = my;
	mM[3][2] = mz;
	//���̍s���Ԃ�
	return *this;
}

void CMatrix::M(int row, int col, float value)
{
	mM[row][col] = value;
}

//*���Z�q�̃I�[�o�[���[�h
//CMatrix * CMatrix �̉��Z���ʂ�Ԃ�
const CMatrix CMatrix::operator*(const CMatrix& m) const {
	CMatrix t;
	for (int i = 0; i < 4; i++)
	{
		t.mM[i][0] = mM[i][0] * m.mM[0][0] + mM[i][1] * m.mM[1][0] + mM[i][2] * m.mM[2][0] + mM[i][3] * m.mM[3][0];
		t.mM[i][1] = mM[i][0] * m.mM[0][1] + mM[i][1] * m.mM[1][1] + mM[i][2] * m.mM[2][1] + mM[i][3] * m.mM[3][1];
		t.mM[i][2] = mM[i][0] * m.mM[0][2] + mM[i][1] * m.mM[1][2] + mM[i][2] * m.mM[2][2] + mM[i][3] * m.mM[3][2];
		t.mM[i][3] = mM[i][0] * m.mM[0][3] + mM[i][1] * m.mM[1][3] + mM[i][2] * m.mM[2][3] + mM[i][3] * m.mM[3][3];
	}
	return t;
}

float* CMatrix::M() const
{
	return (float*)mM[0];
}

CVector CMatrix::VectorZ() const
{
	return CVector(mM[2][0], mM[2][1], mM[2][2]);
}

CVector CMatrix::VectorX() const
{
	return CVector(mM[0][0], mM[0][1], mM[0][2]);
}

CVector CMatrix::VectorY() const
{
	return CVector(mM[1][0], mM[1][1], mM[1][2]);
}


CMatrix CMatrix::Transpose() const
{
	CMatrix tmp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp.mM[i][j] = mM[j][i];
		}
	}
	return tmp;
}

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

CMatrix::CMatrix()
{
	Identity();
}

CMatrix CMatrix::Identity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mM[i][j] = 0.0f;
			if (i == j)
			{
				mM[i][j] = 1.0f;
			}
		}
	}
	//���̍s���Ԃ�
	return *this;
}

//�g��k���s��̍쐬
//Scale(�{��X, �{��Y, �{��Z)
CMatrix CMatrix::Scale(float sx, float sy, float sz) {
	Identity();
	mM[0][0] = sx;
	mM[1][1] = sy;
	mM[2][2] = sz;
	//���̍s���Ԃ�
	return *this;
}

float CMatrix::M(int r, int c) const
{
	return mM[r][c];
}

