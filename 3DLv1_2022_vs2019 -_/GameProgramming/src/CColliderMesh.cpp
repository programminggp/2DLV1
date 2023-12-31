#include "CCOlliderMesh.h"

CColliderMesh::CColliderMesh()
	:mpColliderTriangles(nullptr)
{
}

CColliderMesh::~CColliderMesh()
{
	//if (mpColliderTriangles != nullptr)
	//{    //�O�p�R���C�_�z��̍폜
	//	delete[] mpColliderTriangles;
	//}
	for (auto idx : mpColliders)
	{
		delete idx;
	}
}

//Set(�e�A�e�s��A���f��)
//���f������O�p�R���C�_�̐���
void CColliderMesh::Set(CCharacter3* parent, CMatrix* matrix, CModel* model)
{   //���f������O�p�|���S���ŎO�p�R���C�_�̔z��쐬
	//mpColliderTriangles = new
	//	CColliderTriangle[model->Triangles().size()];
	for (size_t i = 0; i < model->Triangles().size(); i++)
	{   //�O�p�R���C�_�̐ݒ�
		mpColliders.push_back(new CColliderTriangle(parent, matrix
			, model->Triangles()[i].V0()
			, model->Triangles()[i].V1()
			, model->Triangles()[i].V2()));
//		mpColliderTriangles[i].ChangePriority();
	}
}