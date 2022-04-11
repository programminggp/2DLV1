#include "CMatrix.h"
//�W�����o�͊֐��̃C���N���[�h
#include <stdio.h>
//�~����M_PI��L���ɂ���
#define _USE_MATH_DEFINES
//���w�֐��̃C���N���[�h
#include<math.h>

//�f�t�H���g�R���X�g���N�^
CMatrix::CMatrix() {
	Identity();
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
//�P�ʍs��̍쐬
CMatrix CMatrix::Identity() {
	mM[0][0] = 1, mM[0][1] = 0, mM[0][2] = 0, mM[0][3] = 0;
	mM[1][0] = 0, mM[1][1] = 1, mM[1][2] = 0, mM[1][3] = 0;
	mM[2][0] = 0, mM[2][1] = 0, mM[2][2] = 1, mM[2][3] = 0;
	mM[3][0] = 0, mM[3][1] = 0, mM[3][2] = 0, mM[3][3] = 1;
	//���̍s���Ԃ�
	return *this;
}
// �g��k���s��̍쐬
//Scale(�{��X,�{��Y,�{��Z)
CMatrix CMatrix::Scale(float sx, float sy, float sz) {
	mM[0][0] = sx, mM[0][1] = 0, mM[0][2] = 0, mM[0][3] = 0;
	mM[1][0] = 0, mM[1][1] = sy, mM[1][2] = 0, mM[1][3] = 0;
	mM[2][0] = 0, mM[2][1] = 0, mM[2][2] = sz, mM[2][3] = 0;
	mM[3][0] = 0, mM[3][1] = 0, mM[3][2] = 0, mM[3][3] = 1;
	//���̍s���Ԃ�
	return *this;
}
//2�����z��mM��r�sc��̒l��Ԃ��܂�
float CMatrix::M(int r, int c)const
{
	//���̍s���Ԃ�
	return mM[r][c];
};
//��]�s��(X��)�̍쐬
//RotateX(�p�x
CMatrix CMatrix::RotateX(float degree) {
	float rad = degree / 180.0f * M_PI;
	//�P�ʍs��ɂ���
	Identity();
	mM[1][1] = mM[2][2] = cosf(rad);
	mM[2][1] = -sinf(rad);
	mM[1][2] = -mM[2][1];
	//�s���Ԃ�
	return *this;
}
//��]�s��(Y��)�̍쐬
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
//��]�s��(Z��)�̍쐬
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
//�ړ��s��̍쐬
//Translate(�ړ���X,�ړ���Y,�ړ���Z)
CMatrix CMatrix::Translate(float mx, float my, float mz)
{
	//�P�ʍs��ɂ���
	Identity();
	mM[3][0] = mx;
	mM[3][1] = my;
	mM[3][2] = mz;
	//���̍s���Ԃ�
	return *this;
}
//�z���������
void CMatrix::M(int row, int col, float value)
{
	mM[row][col] = value;
}
//*���Z�q�̃I�[�o�[���[�h
//CMatrix * CMatrix�̉��Z���ʂ�Ԃ�
CMatrix CMatrix::operator*(const CMatrix& m) {
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
float* CMatrix::M() const {
	return(float*)mM[0];
}

