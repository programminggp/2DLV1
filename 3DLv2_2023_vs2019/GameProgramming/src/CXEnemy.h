#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CColliderCapsule.h"

class CXEnemy : public CXCharacter
{
public:
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);
	CXEnemy();
	void Init(CModelX* model);
private:
	//�R���C�_�̐錾
	CColliderCapsule mColBody;	//��
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword0;	//��
	CCollider mColSphereSword1;	//��
	CCollider mColSphereSword2;	//��
};


#endif
