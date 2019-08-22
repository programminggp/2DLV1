#include "CMatrix.h"
#define _USE_MATH_DEFINES
#include <math.h>

CMatrix::CMatrix() {
	Identity();
}

void CMatrix::Identity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mM[i][j] = 0.0f;
		}
	}
	mM[0][0] = mM[1][1] = mM[2][2] = mM[3][3] = 1.0f;
}

void CMatrix::RotateY(float degree) {
	float rad = degree / 180.0f * M_PI;
	Identity();
	mM[0][0] = mM[2][2] = cosf(rad);
	mM[0][2] = -sinf(rad);
	mM[2][0] = -mM[0][2];
}

void CMatrix::RotateX(float degree) {
	float rad = degree / 180.0f * M_PI;
	Identity();
	mM[1][1] = mM[2][2] = cosf(rad);
	mM[1][2] = sinf(rad);
	mM[2][1] = -mM[1][2];
}
