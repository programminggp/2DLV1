#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
: mpColliderTriangles(0)
{
}

CColliderMesh::~CColliderMesh()
{
	if (mpColliderTriangles)
	{	//�O�p�R���C�_�z��̍폜
		delete[] mpColliderTriangles;
	}
}

//Set(�e, �e�s��, ���f��)
//���f������O�p�R���C�_�̐���
void CColliderMesh::Set(CCharacter *parent, CMatrix *matrix, CModel *model)
{	//���f���̎O�p�|���S���ŎO�p�R���C�_�̔z��쐬
	mpColliderTriangles = new CColliderTriangle[model->mTriangles.size()];
	for (int i = 0; i < model->mTriangles.size(); i++)
	{	//�O�p�R���C�_�̐ݒ�
		mpColliderTriangles[i].Set(parent, matrix
			, model->mTriangles[i].mV[0]
			, model->mTriangles[i].mV[1]
			, model->mTriangles[i].mV[2]);
		mpColliderTriangles[i].ChangePriority();
	}
}
