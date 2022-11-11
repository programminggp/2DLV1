#pragma once
#include "CXCharacter.h"
#include "CCollider.h"
#include "CColliderCapsule.h"

class CXEnemy : public CXCharacter
{
public:
	CXEnemy(const CVector& pos, const CVector& rot, CVector& scale);
	CXEnemy();
	void Init(CModelX* model);
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);
private:
	static CModelX mModel;
	//�R���C�_�̐錾
	CColliderCapsule mColCapsBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword0;	//��
	CCollider mColSphereSword1;	//��
	CCollider mColSphereSword2;	//��
};