#ifndef CVECTOR
#define CVECTOR

class CMatrix;

class CVector {
public:
	float mX, mY, mZ;
	CVector();
	CVector(float x, float y, float z);
	void Set(float x, float y, float z);
	CVector operator * (const CMatrix &m) const;
};

#endif
