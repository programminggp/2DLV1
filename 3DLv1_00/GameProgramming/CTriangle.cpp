#include "CTriangle.h"
#include "CMatrix.h"
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
	mNormal[0].mX = mNormal[1].mX = mNormal[2].mX = x;
	mNormal[0].mY = mNormal[1].mY = mNormal[2].mY = y;
	mNormal[0].mZ = mNormal[1].mZ = mNormal[2].mZ = z;
}


void CTriangle::SetVertex(CVector v0, CVector v1, CVector v2) {
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

void CTriangle::Render() {
	glBegin(GL_TRIANGLES);
	glNormal3f(mNormal[0].mX, mNormal[0].mY, mNormal[0].mZ);
	glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
	glNormal3f(mNormal[1].mX, mNormal[1].mY, mNormal[1].mZ);
	glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
	glNormal3f(mNormal[2].mX, mNormal[2].mY, mNormal[2].mZ);
	glVertex3f(mV[2].mX, mV[2].mY, mV[2].mZ);
	glEnd();
}

void CTriangle::Render(const CMatrix &matrix) {
	CMatrix m = matrix;
	CVector V[3], Normal[3];
	V[0] = mV[0] * m;
	V[1] = mV[1] * m;
	V[2] = mV[2] * m;
	m.mM[3][0] = m.mM[3][1] = m.mM[3][2] = 0.0f;
	Normal[0] = mNormal[0] * m;
	Normal[1] = mNormal[1] * m;
	Normal[2] = mNormal[2] * m;
//	glNormal3f(Normal.mX, Normal.mY, Normal.mZ);
	glBegin(GL_TRIANGLES);
	glNormal3f(Normal[0].mX, Normal[0].mY, Normal[0].mZ);
	glVertex3f(V[0].mX, V[0].mY, V[0].mZ);
	glNormal3f(Normal[1].mX, Normal[1].mY, Normal[1].mZ);
	glVertex3f(V[1].mX, V[1].mY, V[1].mZ);
	glNormal3f(Normal[2].mX, Normal[2].mY, Normal[2].mZ);
	glVertex3f(V[2].mX, V[2].mY, V[2].mZ);
	//glVertex3f(V[0].mX, V[0].mY, V[0].mZ);
	//glVertex3f(V[1].mX, V[1].mY, V[1].mZ);
	//glVertex3f(V[2].mX, V[2].mY, V[2].mZ);
	glEnd();
}
