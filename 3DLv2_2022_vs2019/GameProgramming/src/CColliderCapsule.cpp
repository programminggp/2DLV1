#include "CColliderCapsule.h"
#include "CCollisionManager.h"

CColliderCapsule::CColliderCapsule(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, float radius)
{
	Set(parent, matrix, v0, v1, radius);
}

void CColliderCapsule::Set(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, float radius) {
	mType = ECAPSUL;//�J�v�Z���R���C�_
	mpParent = parent;//�e�ݒ�
	if (matrix)
		mpMatrix = matrix;//�e�s�񂠂�ΐݒ�
	//�O�p�`���_�ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mRadius = radius;
}

void CColliderCapsule::Render()
{
	//�s��ޔ�
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	//�s��K�p
	glMultMatrixf(mpMatrix->M());

	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//���C�g�I�t
	glDisable(GL_LIGHTING);

	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f, 0.0f, 0.0f, 0.4f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	GLUquadric* mesh;
	mesh = gluNewQuadric();
	gluCylinder(mesh, mRadius, mRadius, (mV[0]-mV[1]).Length()- mRadius*2, 16, 16);

	//�O�p�`�`��
	//glBegin(GL_LINES);
	//glVertex3f(mV[0].X(), mV[0].Y(), mV[0].Z());
	//glVertex3f(mV[1].X(), mV[1].Y(), mV[1].Z());
	//glEnd();

	//���C�g�I��
	glEnable(GL_LIGHTING);
	//�A���t�@�u�����h����
	glDisable(GL_ALPHA);
	//�s�񕜋A
	glPopMatrix();
}
//�D��x�̕ύX
void CColliderCapsule::ChangePriority()
{
	//mV[0]��mV[1]�̒��S�����߂�
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix) * (0.5f);
	//�x�N�g���̒������D��x
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this); //��U�폜
	CCollisionManager::Get()->Add(this); //�ǉ�
}
