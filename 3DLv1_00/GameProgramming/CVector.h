#ifndef CVECTOR
#define CVECTOR

class CMatrix;

class CVector {
public:
	float mX, mY, mZ;
	CVector();
	CVector(float x, float y, float z);
	void Set(float x, float y, float z);
	CVector Multi(const CMatrix &m);
	CVector operator*(const CMatrix &m);
};

#endif
