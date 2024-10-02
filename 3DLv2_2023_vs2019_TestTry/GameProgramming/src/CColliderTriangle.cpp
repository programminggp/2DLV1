#include "CColliderTriangle.h"
#include "CCollisionManager.h"

void CColliderTriangle::ChangePriority()
{
	//mV[0]��mV[1]��mV[2]�̒��S�����߂�
//	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix
//		+ mV[2] * *mpMatrix) * (1.0f / 3.0f);
	CVector pos = (mV[0] + mV[1] + mV[2]) * (1.0f / 3.0f);
	//�x�N�g���̒������D��x
	CCollider::ChangePriority(pos.Length());
}

CColliderTriangle::CColliderTriangle(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1, const CVector& v2)
{
	Set(parent, matrix, v0, v1, v2);
}

void CColliderTriangle::Set(CCharacter3* parent, CMatrix* matrix
	, const CVector& v0, const CVector& v1, const CVector& v2) {
	mType = ETRIANGLE;//�O�p�R���C�_
	mpParent = parent;//�e�ݒ�
	if (matrix)
		mpMatrix = matrix;//�e�s�񂠂�ΐݒ�
	//�O�p�`���_�ݒ�
	mV0 = mV[0] = v0;
	mV1 = mV[1] = v1;
	mV2 = mV[2] = v2;
}

void CColliderTriangle::Render()
{
	//�s��ޔ�
	glPushMatrix();
	//�s��K�p
	glMultMatrixf(mpMatrix->M());
	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//���C�g�I�t
	glDisable(GL_LIGHTING);

	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f, 0.0f, 0.0f, 0.2f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//�O�p�`�`��
	glBegin(GL_TRIANGLES);
	glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	glVertex3f(mV[2].X(), mV[2].Y(), mV[2].Z());
	glEnd();

	//���C�g�I��
	glEnable(GL_LIGHTING);
	//�A���t�@�u�����h����
	glDisable(GL_ALPHA);
	//�s�񕜋A
	glPopMatrix();
}

void CColliderTriangle::Update()
{
	mV[0] = mV0 * *mpMatrix;
	mV[1] = mV1 * *mpMatrix;
	mV[2] = mV2 * *mpMatrix;
	mV[3] = (mV[1] - mV[0]).Cross(mV[2] - mV[0]).Normalize();
	ChangePriority();
}