#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
#include <list>
#include "CCollisionManager2.h"

/*
���f���f�[�^����O�p�R���C�_�̐���
*/
class CColliderMesh
{
public:
	void ChangePriority();
	CColliderMesh();
	~CColliderMesh();
	//Set(�e�A�e�s��A���f��)
	//���f������O�p�R���C�_�̐���
	void Set(CCharacter3* parent, CMatrix* matrix, CModel *model);
private:
	std::list<CColliderTriangle*> mpColliders;
	//�O���R���C�_�̔z��쐬
	CColliderTriangle* mpColliderTriangles;
//	CTaskManager2 mColliders;
};
#endif
