#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
#include <list>
#include "CColliderManager.h"

/*
���f���f�[�^����O�p�R���C�_�̐���
*/
class CColliderMesh
{
public:
	CColliderMesh();
	~CColliderMesh();
	//Set(�e�A�e�s��A���f��)
	//���f������O�p�R���C�_�̐���
	void Set(CCharacter3* parent, CMatrix* matrix, CModel *model);
private:
	//�O�p�R���C�_�̃��X�g
	std::list<CColliderTriangle*> mpColliders;
};
#endif
