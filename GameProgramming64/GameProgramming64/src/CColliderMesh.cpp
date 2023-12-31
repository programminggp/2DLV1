#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
{
}

CColliderMesh::~CColliderMesh()
{
	//�O�p�R���C�_�̍폜
	for (auto col : mpColliders)
	{
		delete col;
	}
}

//Set(�e, �e�s��, ���f��)
//���f������O�p�R���C�_�̐���
void CColliderMesh::Set(CCharacter *parent, CMatrix *matrix, CModel *model)
{	
	for (size_t i = 0; i < model->Triangles().size(); i++)
	{	//�O�p�R���C�_�̐���
		mpColliders.push_back(new CColliderTriangle(parent, matrix
			, model->Triangles()[i].V0()
			, model->Triangles()[i].V1()
			, model->Triangles()[i].V2()));
	}
}
