#ifndef CTRIANGLE
#define CTRIANGLE
#include "CVector.h"

class CTriangle {
public:
	CVector mV[3];
	CVector mNormal;
	CTriangle();
	CTriangle(CVector v0, CVector v1, CVector v2);
	void SetVertex(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2);
	void SetNormal(float x, float y, float z);
	void SetVertex(CVector v0, CVector v1, CVector v2);
	void Render();
	void Render(const CMatrix &m);
};

#endif
