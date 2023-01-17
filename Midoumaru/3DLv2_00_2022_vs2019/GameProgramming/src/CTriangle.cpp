#include "CTriangle.h"
#include "glut.h"

void CTriangle::MaterialIdx(int idx)
{
	mMaterialIdx = idx;
}

CTriangle::CTriangle()
	: mMaterialIdx(0)
{
}

int CTriangle::MaterialIdx()
{
	return mMaterialIdx;
}

const CVector& CTriangle::V0() const
{
	return mV[0];
}
const CVector& CTriangle::V1() const
{
	return mV[1];
}
const CVector& CTriangle::V2() const
{
	return mV[2];
}

const CVector& CTriangle::N0() const
{
	return mN[0];
}
const CVector& CTriangle::N1() const
{
	return mN[1];
}
const CVector& CTriangle::N2() const
{
	return mN[2];
}

const CVector& CTriangle::UV0() const
{
	return mUv[0];
}
const CVector& CTriangle::UV1() const
{
	return mUv[1];
}
const CVector& CTriangle::UV2() const
{
	return mUv[2];
}
void CTriangle::SetUv(const CVector& v0, const CVector& v1, const CVector& v2)
{
	mUv[0] = v0;
	mUv[1] = v1;
	mUv[2] = v2;
}

//���_���W�ݒ�
//Vertex(���_1, ���_2, ���_3)
void CTriangle::Vertex(const CVector &v0, const CVector &v1, const CVector &v2) {
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

//�@���ݒ�
//Normal(�@���x�N�g��)
void CTriangle::Normal(const CVector &n) {
	mN[0] = mN[1] = mN[2] = n;
}
//Normal(�@���x�N�g��1, �@���x�N�g��2, �@���x�N�g��3)
void CTriangle::Normal(const CVector &v0, const CVector &v1, const CVector &v2) {
	mN[0] = v0;
	mN[1] = v1;
	mN[2] = v2;
}

//�`��
void CTriangle::Render() {
	glBegin(GL_TRIANGLES);
	glNormal3f(mN[0].X(), mN[0].Y(), mN[0].Z());
	glTexCoord2f(mUv[0].X(), mUv[0].Y());
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glNormal3f(mN[1].X(), mN[1].Y(), mN[1].Z());
	glTexCoord2f(mUv[1].X(), mUv[1].Y());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glNormal3f(mN[2].X(), mN[2].Y(), mN[2].Z());
	glTexCoord2f(mUv[2].X(), mUv[2].Y());
	glVertex3f(mV[2].X(), mV[2].Y(), mV[2].Z());
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
	mat.M(3, 0, 0.0f);
	mat.M(3, 1, 0.0f);
	mat.M(3, 2, 0.0f);
	//	mat.Translate(0.0f, 0.0f, 0.0f);
	//	mat.M()[3][0] = mat.mM[3][1] = mat.mM[3][2] = 0.0f;
	mN[0] = CTriangle::mN[0] * mat;
	mN[1] = CTriangle::mN[1] * mat;
	mN[2] = CTriangle::mN[2] * mat;
	glBegin(GL_TRIANGLES);
	glNormal3f(mN[0].X(), mN[0].Y(), mN[0].Z());
	glTexCoord2f(mUv[0].X(), mUv[0].Y());
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glNormal3f(mN[1].X(), mN[1].Y(), mN[1].Z());
	glTexCoord2f(mUv[1].X(), mUv[1].Y());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glNormal3f(mN[2].X(), mN[2].Y(), mN[2].Z());
	glTexCoord2f(mUv[2].X(), mUv[2].Y());
	glVertex3f(mV[2].X(), mV[2].Y(), mV[2].Z());
	glEnd();
}
