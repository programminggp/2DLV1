#ifndef CRECTANGLE
#define CRECTANGLE
#include "CTriangle.h"
#include "CMatrix.h"

class CRectangle {
public:
	CTriangle mT[2];
	void SetVertex(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	void SetNormal(float x, float y, float z);
	void Render();
	void Render(const CMatrix &m);
};

#endif
