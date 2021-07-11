#include "CBillBoard.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>

CBillBoard::CBillBoard()
{
}

CBillBoard::CBillBoard(CVector pos, float w, float h)
{
	Set(pos, w, h);
}

void CBillBoard::Set(CVector pos, float w, float h) {
	//�ʒu
	mPosition = pos;
	//�傫���̐ݒ�
	mScale.mX = w;
	mScale.mY = h;
	//�O�p�`�̒��_���W�ݒ�
	mT[0].SetVertex(CVector(1.0f, 1.0f, 0.0f),
		CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, -1.0f, 0.0f));
	mT[1].SetVertex(CVector(-1.0f, 1.0f, 0.0f),
		CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, 1.0f, 0.0f));
	//�@����Z������
	mT[0].SetNormal(CVector(0.0f, 0.0f, 1.0f));
	mT[1].SetNormal(CVector(0.0f, 0.0f, 1.0f));
	//�F�𔒐F��ݒ�
	mMaterial.mDiffuse[0] = mMaterial.mDiffuse[1] =
		mMaterial.mDiffuse[2] = mMaterial.mDiffuse[3] = 1.0f;
}


void CBillBoard::Update() {
	//�J�����ւ̕����x�N�g���̎擾
	CVector dir = Camera.mEye - mPosition;
	//Y���̉�]�l�����߂�
	mRotation.mY = atan2f(dir.mX, dir.mZ) * 180.0f / M_PI;
	//X���̉�]�l�����߂�
	mRotation.mX = asinf(-dir.mY / dir.Length()) * 180.0f / M_PI;
	//�s��̍X�V
	CTransform::Update();
}

void CBillBoard::Render()
{
	Render(&mMaterial);
}
//Render(�}�e���A���̃|�C���^)
void CBillBoard::Render(CMaterial *mpMaterial) {
	//�s��̕ۑ�
	glPushMatrix();
	//�g�k�A��]�A�ړ�������
	glMultMatrixf(mMatrix.mM[0]);
	//���C�g�I�t
	glDisable(GL_LIGHTING);
	//�`��F�̐ݒ�
	glColor4fv(mpMaterial->mDiffuse);
	//�}�e���A���K�p
	mpMaterial->Enabled();
	//�O�p�`�̕`��
	mT[0].Render();
	mT[1].Render();
	//�}�e���A������
	mpMaterial->Disabled();
	//���C�g�I��
	glEnable(GL_LIGHTING);
	//�s���߂�
	glPopMatrix();
}
