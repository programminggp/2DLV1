#include "CMatrix.h"
#define _USE_MATH_DEFINES
#include <math.h>

CMatrix::CMatrix() {
	Identity();
}

CMatrix CMatrix::Identity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mM[i][j] = 0.0f;
		}
	}
	mM[0][0] = mM[1][1] = mM[2][2] = mM[3][3] = 1.0f;
	return *this;
}

CMatrix CMatrix::RotateY(float degree) {
	float rad = degree / 180.0f * M_PI;
	Identity();
	mM[0][0] = mM[2][2] = cosf(rad);
	mM[0][2] = -sinf(rad);
	mM[2][0] = -mM[0][2];
	return *this;
}

const CMatrix CMatrix::RotateX(float degree) {
	float rad = degree / 180.0f * M_PI;
	Identity();
	mM[1][1] = mM[2][2] = cosf(rad);
	mM[1][2] = sinf(rad);
	mM[2][1] = -mM[1][2];
	return *this;
}

CMatrix CMatrix::Scale(float x, float y, float z) {
	Identity();
	mM[0][0] = x;
	mM[1][1] = y;
	mM[2][2] = z;
	return *this;
}

CMatrix CMatrix::Translate(float x, float y, float z) {
	Identity();
	mM[3][0] = x;
	mM[3][1] = y;
	mM[3][2] = z;
	return *this;
}

CMatrix CMatrix::Multi(const CMatrix &m) {
	CMatrix t;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			t.mM[i][j] = 0.0f;
			for (int k = 0; k < 4; k++) {
				t.mM[i][j] += mM[i][k] * m.mM[k][j];
			}
		}
	}
	return t;
}

CMatrix CMatrix::operator*(const CMatrix &m) {
	return Multi(m);
}
