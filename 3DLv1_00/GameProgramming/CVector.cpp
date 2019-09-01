#include "CVector.h"
#include "CMatrix.h"

CVector::CVector()
: mX(0.0f), mY(0.0f), mZ(0.0f)
{}

CVector::CVector(float x, float y, float z)
: mX(x), mY(y), mZ(z)
{}

void CVector::Set(float x, float y, float z) {
	mX = x;
	mY = y;
	mZ = z;
}

CVector CVector::Multi(const CMatrix &m) {
	CVector v;

	v.mX = mX * m.mM[0][0] + mY * m.mM[1][0] + mZ * m.mM[2][0] + m.mM[3][0];
	v.mY = mX * m.mM[0][1] + mY * m.mM[1][1] + mZ * m.mM[2][1] + m.mM[3][1];
	v.mZ = mX * m.mM[0][2] + mY * m.mM[1][2] + mZ * m.mM[2][2] + m.mM[3][2];

	return v;
}


CVector CVector::operator*(const CMatrix &m) {
	return Multi(m);
}

CVector CVector::operator + (const CVector &v) {
	return CVector(mX + v.mX, mY + v.mY, mZ + v.mZ);
}
