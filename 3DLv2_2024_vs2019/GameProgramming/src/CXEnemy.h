#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"

#include "CCollider.h"
#include "CColliderCapsule.h"

class CXEnemy : public CXCharacter
{
public:
	void Update()
	{
		CXCharacter::Update();
		mColBody.Update();
	}
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	void Init(CModelX* model);
	//�R���C�_�̏�����
	CXEnemy()
		: mColSphereBody(this, nullptr, CVector(0.5f, -1.0f, 0.0f), 1.0f)
		, mColSphereHead(this, nullptr, CVector(0.0f, 1.f, 0.0f), 1.5f)
		, mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f)
		, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f)
		, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f)
		, mColBody(this, nullptr, CVector(0.f, -1.5f, 0.0f),
			CVector(0.f, 1.0f, 0.0f), 1.0f)
	{
	}
private:
	CColliderCapsule mColBody;	//��
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword0;	//��
	CCollider mColSphereSword1;	//��
	CCollider mColSphereSword2;	//��
};

#endif
