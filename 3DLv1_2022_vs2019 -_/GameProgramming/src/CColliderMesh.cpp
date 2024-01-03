#include "CCOlliderMesh.h"

CColliderMesh::CColliderMesh()
{
}

CColliderMesh::~CColliderMesh()
{
	//���X�g���̃R���C�_��S�č폜
	for (auto idx : mpColliders)
	{
		delete idx;
	}
}

//Set(�e�A�e�s��A���f��)
//���f������O�p�R���C�_�̐���
void CColliderMesh::Set(CCharacter3* parent, CMatrix* matrix, CModel* model)
{
	//���f������O�p�|���S���ŎO�p�R���C�_�̔z��쐬
	for (size_t i = 0; i < model->Triangles().size(); i++)
	{	//�O�p�R���C�_�𐶐����A���X�g�֒ǉ�
		mpColliders.push_back(
			new CColliderTriangle(parent, matrix
				, model->Triangles()[i].V0()
				, model->Triangles()[i].V1()
				, model->Triangles()[i].V2()));
	}
}
