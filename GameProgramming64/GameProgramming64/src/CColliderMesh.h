#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
#include <list>
/*
���f���f�[�^����O�p�R���C�_�̐���
*/
class CColliderMesh
{
public:
	CColliderMesh();
	~CColliderMesh();
	//Set(�e, �e�s��, ���f��)
	//���f������O�p�R���C�_�̐���
	void Set(CCharacter *parent, CMatrix *matrix, CModel *model);
private:
	//�O�p�R���C�_�̃��X�g
	std::list<CColliderTriangle*> mpColliders;
};

#endif
