#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy : public CXCharacter {
public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	//M
	CCollider mColSphereSword0;	//��
	CCollider mColSphereSword1;	//��
	CCollider mColSphereSword2;	//��

	CXEnemy();
	void Init(CModelX *model);
	//�Փˏ���
	void Collision(CCollider *m, CCollider *y);
};

#endif
