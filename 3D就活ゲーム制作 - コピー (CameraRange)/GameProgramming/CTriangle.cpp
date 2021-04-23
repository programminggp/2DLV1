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

//Render(�s��)
void CTriangle::Render(const CMatrix &m) {
	//���_�Ɩ@���̍쐬
	CVector V[3], N;
	//�s����|����
	V[0] = mV[0] * m;
	V[1] = mV[1] * m;
	V[2] = mV[2] * m;
	//�@���͕��s�ړ��͂����Ȃ�
	//�s����R�s�[
	CMatrix nm = m;
	//�ړ��v�f��0�ɂ���
	nm.mM[3][0] = nm.mM[3][1] = nm.mM[3][2] = 0.0f;
	//��]�̂݌v�Z����
	N = mN[0] * nm;
	//���Z��̍��W�ŕ`�悷��
	glBegin(GL_TRIANGLES);
	glNormal3f(N.mX, N.mY, N.mZ);
	glVertex3f(V[0].mX, V[0].mY, V[0].mZ);
	N = mN[1] * nm;
	glNormal3f(N.mX, N.mY, N.mZ);
	glVertex3f(V[1].mX, V[1].mY, V[1].mZ);
	N = mN[2] * nm;
	glNormal3f(N.mX, N.mY, N.mZ);
	glVertex3f(V[2].mX, V[2].mY, V[2].mZ);
	glEnd();
}
