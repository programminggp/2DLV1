#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H

#include "CModel.h"
#include "CColliderTriangle.h"
/*
���f���f�[�^����O�p�`�R���C�_�̐���
*/
class CColliderMesh
{
public:
	CColliderTriangle *mpColliderTriangles;
	CColliderMesh();
	~CColliderMesh();
	//Set(���f��)
	void Set(CModel *model);
};

#endif
