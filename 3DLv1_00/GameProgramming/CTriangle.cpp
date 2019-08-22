#include "CTriangle.h"
#include "glut.h"

CTriangle::CTriangle(){}

CTriangle::CTriangle(CVector v0, CVector v1, CVector v2) {
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

void CTriangle::SetVertex(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2) {
	mV[0].mX = x0;
	mV[0].mY = y0;
	mV[0].mZ = z0;
	mV[1].mX = x1;
	mV[1].mY = y1;
	mV[1].mZ = z1;
	mV[2].mX = x2;
	mV[2].mY = y2;
	mV[2].mZ = z2;
}


void CTriangle::SetNormal(float x, float y, float z) {
	mNormal.mX = x;
	mNormal.mY = y;
	mNormal.mZ = z;
}


void CTriangle::SetVertex(CVector v0, CVector v1, CVector v2) {
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

void CTriangle::Render() {
	glNormal3f(mNormal.mX, mNormal.mY, mNormal.mZ);
	glBegin(GL_TRIANGLES);
	glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
	glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
	glVertex3f(mV[2].mX, mV[2].mY, mV[2].mZ);
	glEnd();
}

void CTriangle::Render(const CMatrix &m) {
	CVector V[3], Normal;
	V[0] = mV[0] * m;
	V[1] = mV[1] * m;
	V[2] = mV[2] * m;
	Normal = mNormal * m;
	glNormal3f(Normal.mX, Normal.mY, Normal.mZ);
	glBegin(GL_TRIANGLES);
	glVertex3f(V[0].mX, V[0].mY, V[0].mZ);
	glVertex3f(V[1].mX, V[1].mY, V[1].mZ);
	glVertex3f(V[2].mX, V[2].mY, V[2].mZ);
	glEnd();
}
