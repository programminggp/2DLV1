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
