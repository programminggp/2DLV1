#include "CColliderTriangle.h"

CColliderTriangle::CColliderTriangle(
	CCharacter3* parent, 
	CMatrix* matrix, 
	const CVector& v0, 
	const CVector& v1, 
	const CVector& v2)
{
	Set(parent, matrix, v0, v1, v2);
}

void CColliderTriangle::Set(
	CCharacter3* parent, 
	CMatrix* matrix, 
	const CVector& v0, 
	const CVector& v1, 
	const CVector& v2)
{
	mType = EType::ETRIANGLE;//�O�p�R���C�_
	mpParent = parent;//�e�ݒ�
	if (matrix)
		mpMatrix = matrix;//�e�s�񂠂�ΐݒ�
	//�O�p�`���_�ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
	Update();
}

void CColliderTriangle::Render()
{
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
	glVertex3f(CCollider::mV[0].X(), CCollider::mV[0].Y(), CCollider::mV[0].Z());
	glVertex3f(CCollider::mV[1].X(), CCollider::mV[1].Y(), CCollider::mV[1].Z());
	glVertex3f(CCollider::mV[2].X(), CCollider::mV[2].Y(), CCollider::mV[2].Z());
	glEnd();

	//���C�g�I��
	glEnable(GL_LIGHTING);
	//�A���t�@�u�����h����
	glDisable(GL_ALPHA);
}

void CColliderTriangle::Update()
{
	CCollider::mV[0] = mV[0] * *mpMatrix;
	CCollider::mV[1] = mV[1] * *mpMatrix;
	CCollider::mV[2] = mV[2] * *mpMatrix;
	CCollider::mV[3] = (CCollider::mV[1] - CCollider::mV[0]).Cross(CCollider::mV[2] - CCollider::mV[0]).Normalize();
	ChangePriority();
}

void CColliderTriangle::ChangePriority()
{
	//mV[0]��mV[1]��mV[2]�̒��S�����߂�
	CVector pos = (CCollider::mV[0] + CCollider::mV[1] + CCollider::mV[2]) * (1.0f / 3.0f);
	//�x�N�g���̒������D��x
	CCollider::ChangePriority(pos.Length());
}