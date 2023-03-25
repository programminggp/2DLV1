#include "CBillBoard.h"
#include "CApplication.h"

CBillBoard::CBillBoard()
{
}

CBillBoard::CBillBoard(CVector pos, float w, float h)
{
	Set(pos, w, h);
}

CBillBoard::CBillBoard(CVector pos, float w, float h, int priority)
	: CCharacter3(priority)
{
	Set(pos, w, h);
}

void CBillBoard::Set(CVector pos, float w, float h)
{
	//�ʒu
	mPosition = pos;
	//�傫���̐ݒ�
	mScale = CVector(w, h, 1.0f);
	//�O�p�`�̒��_���W�ݒ�
	mT[0].Vertex(CVector(1.0f, 1.0f, 0.0f),
		CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, -1.0f, 0.0f));
	mT[1].Vertex(CVector(-1.0f, 1.0f, 0.0f),
		CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, 1.0f, 0.0f));
	//�@����Z������
	mT[0].Normal(CVector(0.0f, 0.0f, 1.0f));
	mT[1].Normal(CVector(0.0f, 0.0f, 1.0f));
	//�F�𔒐F��ݒ�
	mMaterial.Diffuse()[0] = 1.0f;
	mMaterial.Diffuse()[1] = 1.0f;
	mMaterial.Diffuse()[2] = 1.0f;
	mMaterial.Diffuse()[3] = 1.0f;
}
void CBillBoard::Update()
{
	//�s��̍X�V
	CTransform::Update();
}
void CBillBoard::Render()
{
	Render(&mMaterial);
}
//Render(�}�e���A���̃|�C���^)
void CBillBoard::Render(CMaterial* mpMaterial)
{
	//�s��̕ۑ�
	glPushMatrix();
	//�g�k�A��]�A�ړ�������
	glMultMatrixf((CApplication::ModelViewInverse() *  mMatrix).M());
	//���C�g�I�t
	glDisable(GL_LIGHTING);
	//�`��F�̐ݒ�
	glColor4fv(mpMaterial->Diffuse());
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
