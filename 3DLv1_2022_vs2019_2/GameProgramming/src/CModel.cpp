#include "CModel.h"
#include "glut.h"

#define V1 CVector(1.0f, 0.0f, 0.0f)
#define V2 CVector(0.0f, 1.0f, 0.0f)
#define V3 CVector(0.0f, 0.0f, 1.0f)
#define V4 CVector(-1.0f, 0.0f, 0.0f)
#define N1 CVector(0.5412, 0.7071, 0.5412)
#define N2 CVector(-0.5412, 0.7071, 0.5412)

CModel::CModel()
{
	mVertex[0].mPosition = V1;
	mVertex[0].mNormal = N1;
	mVertex[1].mPosition = V2;
	mVertex[1].mNormal = N1;
	mVertex[2].mPosition = V3;
	mVertex[2].mNormal = N1;

	mVertex[3].mPosition = V2;
	mVertex[3].mNormal = N2;
	mVertex[4].mPosition = V4;
	mVertex[4].mNormal = N2;
	mVertex[5].mPosition = V3;
	mVertex[5].mNormal = N2;

	for (int i = 0; i < 6; i++)
	{
		mVector.push_back(mVertex[i]);
	}
}

void CModel::Render()
{
	//���_���W�̈ʒu��ݒ�
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CVertex), (void*)&mVector[0].mPosition);
	//�@���x�N�g���̈ʒu��ݒ�
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CVertex), (void*)&mVector[0].mNormal);

	//�`��ʒu����̃f�[�^�ŎO�p�`��`�悵�܂�
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//���_���W�̔z��𖳌��ɂ���
	glDisableClientState(GL_VERTEX_ARRAY);
	//�@���̔z��𖳌��ɂ���
	glDisableClientState(GL_NORMAL_ARRAY);
}
