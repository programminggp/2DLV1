#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
/*
���f���f�[�^����O�p�R���C�_�̐���
*/
class CColliderMesh
{
public:
	//�O�p�R���C�_�̔z��쐬
	CColliderTriangle *mpColliderTriangles;
	CColliderMesh();
	~CColliderMesh();
	//Set(�e, �e�s��, ���f��)
	//���f������O�p�R���C�_�̐���
	void Set(CCharacter *parent, CMatrix *matrix, CModel *model);
};

#endif
