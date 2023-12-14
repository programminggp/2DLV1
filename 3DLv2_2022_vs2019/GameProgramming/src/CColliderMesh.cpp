#include "CColliderMesh.h"

CColliderMesh::CColliderMesh()
: mpColliderTriangles(nullptr)
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
	mpColliderTriangles = new CColliderTriangle[model->Triangles().size()];
#ifdef _DEBUG
	CVector max, min;
	CColliderTriangle coltri;
	coltri.Set(parent, matrix
		, model->Triangles()[0].V0()
		, model->Triangles()[0].V1()
		, model->Triangles()[0].V2());
	max = coltri.WorldGreater();
	min = coltri.WorldLess();
#endif
	for (size_t i = 0; i < model->Triangles().size(); i++)
	{	//�O�p�R���C�_�̐ݒ�
		mpColliderTriangles[i].Set(parent, matrix
			, model->Triangles()[i].V0()
			, model->Triangles()[i].V1()
			, model->Triangles()[i].V2());
		//mpColliderTriangles[i].ChangePriority();
#ifdef _DEBUG
		max = max.Greater(mpColliderTriangles[i].WorldGreater());
		min = min.Less(mpColliderTriangles[i].WorldLess());
#endif
	}
#ifdef _DEBUG
	printf("MAX:%10f %10f %10f\n", max.X(), max.Y(), max.Z());
	printf("MIN:%10f %10f %10f\n", min.X(), min.Y(), min.Z());
#endif
}
