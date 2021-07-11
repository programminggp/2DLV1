#include "CColliderLine.h"
#include "CCollisionManager.h"

CColliderLine::CColliderLine(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1)
{
	Set(parent, matrix, v0, v1);
}

void CColliderLine::Set(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1) {
	mType = ELINE;//�����R���C�_
	mpParent = parent;//�e�ݒ�
	if (matrix)
		mpMatrix = matrix;//�e�s�񂠂�ΐݒ�
	//�O�p�`���_�ݒ�
	mV[0] = v0;
	mV[1] = v1;
}

void CColliderLine::Render()
{
	//�s��ޔ�
	glPushMatrix();
	//�s��K�p
	glMultMatrixf(mpMatrix->mM[0]);

	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//���C�g�I�t
	glDisable(GL_LIGHTING);

	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//�O�p�`�`��
	glBegin(GL_LINES);
	glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
	glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
	glEnd();

	//���C�g�I��
	glEnable(GL_LIGHTING);
	//�A���t�@�u�����h����
	glDisable(GL_ALPHA);
	//�s�񕜋A
	glPopMatrix();
}
//�D��x�̕ύX
void CColliderLine::ChangePriority()
{
	//mV[0]��mV[1]�̒��S�����߂�
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix) * (0.5f);
	//�x�N�g���̒������D��x
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this); //��U�폜
	CCollisionManager::Get()->Add(this); //�ǉ�
}
