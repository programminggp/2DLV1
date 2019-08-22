#include "CRectangle.h"

void CRectangle::SetVertex(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
	mT[0].SetVertex(x0, y0, z0, x1, y1, z1, x2, y2, z2);
	mT[1].SetVertex(x0, y0, z0, x2, y2, z2, x3, y3, z3);
}

void CRectangle::SetNormal(float x, float y, float z) {
	mT[0].SetNormal(x, y, z);
	mT[1].SetNormal(x, y, z);
}

void CRectangle::Render() {
	mT[0].Render();
	mT[1].Render();
}

void CRectangle::Render(const CMatrix &m) {
	mT[0].Render(m);
	mT[1].Render(m);
}
