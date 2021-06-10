#include "CMatrix.h"
//�W�����o�͊֐��̃C���N���[�h
#include <stdio.h>
//�~����M_PI��L���ɂ���
#define _USE_MATH_DEFINES
//���w�֐��̃C���N���[�h
#include <math.h>


//�\���m�F�p
void CMatrix::Print() {
	printf("%10f %10f %10f %10f \n",
		mM[0][0], mM[0][1], mM[0][2], mM[0][3]);
	printf("%10f %10f %10f %10f \n",
		mM[1][0], mM[1][1], mM[1][2], mM[1][3]);
	printf("%10f %10f %10f %10f \n",
		mM[2][0], mM[2][1], mM[2][2], mM[2][3]);
	printf("%10f %10f %10f %10f \n",
		mM[3][0], mM[3][1], mM[3][2], mM[3][3]);
	/*
	printf("%f %f %f %f \n",
		mM[0][0], mM[0][1], mM[0][2], mM[0][3]);
	printf("%18.8f %18.6f %18.4f %18.2f \n",
		mM[1][0], mM[1][1], mM[1][2], mM[1][3]);
	printf("%.8f %.6f %.4f %.2f \n",
		mM[2][0], mM[2][1], mM[2][2], mM[2][3]);
	printf("%10f %10f %10f %10f \n",
		mM[3][0], mM[3][1], mM[3][2], mM[3][3]);
	*/
}

//�f�t�H���g�R���X�g���N�^
CMatrix::CMatrix() {
	Identity();
}

//�P�ʍs��̍쐬
CMatrix CMatrix::Identity() {
	mM[0][0] = mM[0][1] = mM[0][2] = mM[0][3] = 0.0f;
	mM[1][0] = mM[1][1] = mM[1][2] = mM[1][3] = 0.0f;
	mM[2][0] = mM[2][1] = mM[2][2] = mM[2][3] = 0.0f;
	mM[3][0] = mM[3][1] = mM[3][2] = mM[3][3] = 0.0f;
	mM[0][0] = mM[1][1] = mM[2][2] = mM[3][3] = 1.0f;
	//�s���Ԃ�
	return *this;
}

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
	//���̍s���Ԃ�
	return *this;
}

CMatrix CMatrix::RotateX(float degree) {
	float rad = degree / 180.0f * M_PI;
	Identity();
	mM[1][1] = mM[2][2] = cosf(rad);
	mM[1][2] = sinf(rad);
	mM[2][1] = -mM[1][2];
	return *this;
}

CMatrix CMatrix::RotateZ(float degree) {
	float rad = degree / 180.0f * M_PI;
	Identity();
	mM[0][0] = mM[1][1] = cosf(rad);
	mM[0][1] = sinf(rad);
	mM[1][0] = -mM[0][1];
	return *this;
}

//���s�ړ��s��̍쐬
//Translate(�ړ���X, �ړ���Y, �ړ���Z)
CMatrix CMatrix::Translate(float x, float y, float z) {
	Identity();
	mM[3][0] = x;
	mM[3][1] = y;
	mM[3][2] = z;
	//���̍s���Ԃ�
	return *this;
}

//�g��k���s��̍쐬
//Scale(�{��X, �{��Y, �{��Z)
CMatrix CMatrix::Scale(float x, float y, float z) {
	Identity();
	mM[0][0] = x;
	mM[1][1] = y;
	mM[2][2] = z;
	//���̍s���Ԃ�
	return *this;
}
//*���Z�q�̃I�[�o�[���[�h
//CMatrix * CMatrix �̉��Z���ʂ�Ԃ�
CMatrix CMatrix::operator*(const CMatrix &m) {
	CMatrix t;
	//t.mM[0][0] = mM[0][0] * m.mM[0][0] + mM[0][1] * m.mM[1][0] + mM[0][2] * m.mM[2][0] + mM[0][3] * m.mM[3][0];
	//t.mM[0][1] = mM[0][0] * m.mM[0][1] + mM[0][1] * m.mM[1][1] + mM[0][2] * m.mM[2][1] + mM[0][3] * m.mM[3][1];
	//t.mM[0][2] = mM[0][0] * m.mM[0][2] + mM[0][1] * m.mM[1][2] + mM[0][2] * m.mM[2][2] + mM[0][3] * m.mM[3][2];
	//t.mM[0][3] = mM[0][0] * m.mM[0][3] + mM[0][1] * m.mM[1][3] + mM[0][2] * m.mM[2][3] + mM[0][3] * m.mM[3][3];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			t.mM[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				t.mM[i][j] += mM[i][k] * m.mM[k][j];
			}
		}
	}
	return t;
}

/*
getInverse
�t�s��̎擾
*/
CMatrix CMatrix::GetInverse(void)
{
	float det = 0.0f;
	det += m00 * m11 * m22 * m33 + m00 * m12 * m23 * m31 + m00 * m13 * m21 * m32;
	det += m01 * m10 * m23 * m32 + m01 * m12 * m20 * m33 + m01 * m13 * m22 * m30;
	det += m02 * m10 * m21 * m33 + m02 * m11 * m23 * m30 + m02 * m13 * m20 * m31;
	det += m03 * m10 * m22 * m31 + m03 * m11 * m20 * m32 + m03 * m12 * m21 * m30;

	det -= m00 * m11 * m23 * m32 + m00 * m12 * m21 * m33 + m00 * m13 * m22 * m31;
	det -= m01 * m10 * m22 * m33 + m01 * m12 * m23 * m30 + m01 * m13 * m20 * m32;
	det -= m02 * m10 * m23 * m31 + m02 * m11 * m20 * m33 + m02 * m13 * m21 * m30;
	det -= m03 * m10 * m21 * m32 + m03 * m11 * m22 * m30 + m03 * m12 * m20 * m31;

	CMatrix b;

	b.m00 = m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31;
	b.m01 = m01 * m23 * m32 + m02 * m21 * m33 + m03 * m22 * m31 - m01 * m22 * m33 - m02 * m23 * m31 - m03 * m21 * m32;
	b.m02 = m01 * m12 * m33 + m02 * m13 * m31 + m03 * m11 * m32 - m01 * m13 * m32 - m02 * m11 * m33 - m03 * m12 * m31;
	b.m03 = m01 * m13 * m22 + m02 * m11 * m23 + m03 * m12 * m21 - m01 * m12 * m23 - m02 * m13 * m21 - m03 * m11 * m22;

	b.m10 = m10 * m23 * m32 + m12 * m20 * m33 + m13 * m22 * m30 - m10 * m22 * m33 - m12 * m23 * m30 - m13 * m20 * m32;
	b.m11 = m00 * m22 * m33 + m02 * m23 * m30 + m03 * m20 * m32 - m00 * m23 * m32 - m02 * m20 * m33 - m03 * m22 * m30;
	b.m12 = m00 * m13 * m32 + m02 * m10 * m33 + m03 * m12 * m30 - m00 * m12 * m33 - m02 * m13 * m30 - m03 * m10 * m32;
	b.m13 = m00 * m12 * m23 + m02 * m13 * m20 + m03 * m10 * m22 - m00 * m13 * m22 - m02 * m10 * m23 - m03 * m12 * m20;

	b.m20 = m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31 - m10 * m23 * m31 - m11 * m20 * m33 - m13 * m21 * m30;
	b.m21 = m00 * m23 * m31 + m01 * m20 * m33 + m03 * m21 * m30 - m00 * m21 * m33 - m01 * m23 * m30 - m03 * m20 * m31;
	b.m22 = m00 * m11 * m33 + m01 * m13 * m30 + m03 * m10 * m31 - m00 * m13 * m31 - m01 * m10 * m33 - m03 * m11 * m30;
	b.m23 = m00 * m13 * m21 + m01 * m10 * m23 + m03 * m11 * m20 - m00 * m11 * m23 - m01 * m13 * m20 - m03 * m10 * m21;

	b.m30 = m10 * m22 * m31 + m11 * m20 * m32 + m12 * m21 * m30 - m10 * m21 * m32 - m11 * m22 * m30 - m12 * m20 * m31;
	b.m31 = m00 * m21 * m32 + m01 * m22 * m30 + m02 * m20 * m31 - m00 * m22 * m31 - m01 * m20 * m32 - m02 * m21 * m30;
	b.m32 = m00 * m12 * m31 + m01 * m10 * m32 + m02 * m11 * m30 - m00 * m11 * m32 - m01 * m12 * m30 - m02 * m10 * m31;
	b.m33 = m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m00 * m12 * m21 - m01 * m10 * m22 - m02 * m11 * m20;

	CMatrix tmp = b * (1 / det);
	//CMatrix44 nml;
	//nml = (*this) * (*this);
	//CMatrix44 tnml;
	//tnml = tmp * (*this);

	return tmp;
};

CMatrix CMatrix::GetTranspose() {
	CMatrix tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp.mM[i][j] = mM[j][i];
		}
	}
	return tmp;
}

CMatrix CMatrix::operator*(const float& f) const 
{
	CMatrix t;
	for (int i = 0; i < 16; i++)
	{
		t.mF[i] = mF[i] * f;
	}
	return t;
}
