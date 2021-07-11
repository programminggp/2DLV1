#include "CTriangle.h"
#include "glut.h"

//���_���W�ݒ�
//SetVertex(���_1, ���_2, ���_3)
void CTriangle::SetVertex(const CVector &v0, const CVector &v1, const CVector &v2) {
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

//�@���ݒ�
//SetNormal(�@���x�N�g��)
void CTriangle::SetNormal(const CVector &n) {
	mN[0] = mN[1] = mN[2] = n;
}
//SetNormal(�@���x�N�g��1, �@���x�N�g��2, �@���x�N�g��3)
void CTriangle::SetNormal(const CVector &v0, const CVector &v1, const CVector &v2) {
	mN[0] = v0;
	mN[1] = v1;
	mN[2] = v2;
}

//�`��
void CTriangle::Render() {
	glBegin(GL_TRIANGLES);
	glNormal3f(mN[0].mX, mN[0].mY, mN[0].mZ);
	glTexCoord2f(mUv[0].mX, mUv[0].mY);
	glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
	glNormal3f(mN[1].mX, mN[1].mY, mN[1].mZ);
	glTexCoord2f(mUv[1].mX, mUv[1].mY);
	glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
	glNormal3f(mN[2].mX, mN[2].mY, mN[2].mZ);
	glTexCoord2f(mUv[2].mX, mUv[2].mY);
	glVertex3f(mV[2].mX, mV[2].mY, mV[2].mZ);
	glEnd();
}

//�`��
//Render(�s��)
void CTriangle::Render(const CMatrix &m)
{
	CVector mV[3], mN[3];
	mV[0] = CTriangle::mV[0] * m;
	mV[1] = CTriangle::mV[1] * m;
	mV[2] = CTriangle::mV[2] * m;
	//�@���͈ړ��l���폜
	CMatrix mat = m;
	mat.mM[3][0] = mat.mM[3][1] = mat.mM[3][2] = 0.0f;
	mN[0] = CTriangle::mN[0] * mat;
	mN[1] = CTriangle::mN[1] * mat;
	mN[2] = CTriangle::mN[2] * mat;
	glBegin(GL_TRIANGLES);
	glNormal3f(mN[0].mX, mN[0].mY, mN[0].mZ);
	glTexCoord2f(mUv[0].mX, mUv[0].mY);
	glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
	glNormal3f(mN[1].mX, mN[1].mY, mN[1].mZ);
	glTexCoord2f(mUv[1].mX, mUv[1].mY);
	glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
	glNormal3f(mN[2].mX, mN[2].mY, mN[2].mZ);
	glTexCoord2f(mUv[2].mX, mUv[2].mY);
	glVertex3f(mV[2].mX, mV[2].mY, mV[2].mZ);
	glEnd();
}
