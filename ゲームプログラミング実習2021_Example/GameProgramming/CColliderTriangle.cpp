#include "CColliderTriangle.h"
#include "CCollisionManager.h"

CColliderTriangle::CColliderTriangle(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, const CVector &v2)
{
	Set(parent, matrix, v0, v1, v2);
}

void CColliderTriangle::Set(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, const CVector &v2) {
	mType = ETRIANGLE;//�O�p�R���C�_
	mpParent = parent;//�e�ݒ�
	if (matrix)
		mpMatrix = matrix;//�e�s�񂠂�ΐݒ�
	//�O�p�`���_�ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

void CColliderTriangle::Render()
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
	float c[] = { 1.0f, 0.0f, 0.0f, 0.2f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//�O�p�`�`��
	glBegin(GL_TRIANGLES);
	glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
	glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
	glVertex3f(mV[2].mX, mV[2].mY, mV[2].mZ);
	glEnd();

	//���C�g�I��
	glEnable(GL_LIGHTING);
	//�A���t�@�u�����h����
	glDisable(GL_ALPHA);
	//�s�񕜋A
	glPopMatrix();
}
//�D��x�̕ύX
void CColliderTriangle::ChangePriority()
{
	//mV[0]��mV[1]��mV[2]�̒��S�����߂�
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix + mV[2] * *mpMatrix) * (1.0f/3.0f);
	//�x�N�g���̒������D��x
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this); //��U�폜
	CCollisionManager::Get()->Add(this); //�ǉ�
#ifdef _DEBUG

	printf("%d,", mPriority);

#endif
}
