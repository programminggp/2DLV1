#include "CXEnemy.h"


void CXEnemy::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::ESPHERE:
		if (o->Type() == CCollider::ESPHERE)
		{
			if (o->Parent()->Tag() == EPLAYER)
			{
				if (o->Tag() == CCollider::ETag::ESWORD
					&& m->Tag() == CCollider::ETag::EBODY)
				{
					if (CCollider::Collision(m, o))
					{
						//30�t���[�������ă_�E�����A�J��Ԃ��Ȃ�
					//	ChangeAnimation(11, false, 30);
					}
				}
			}
		}
	}
}

CXEnemy::CXEnemy()
	:
	mColBody(this, nullptr, CVector(0.f, -1.0f, 0.0f), CVector(0.f, 1.0f, 0.0f), 1.0f)
	, mColSphereBody(this, nullptr, CVector(0.5f, -1.0f, 0.0f), 1.0f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 1.f, 0.0f), 1.5f)
	, mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f)
	, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f)
	, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f)

{

}


void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColBody.Matrix(&mpCombinedMatrix[1]);
	mColSphereBody.Matrix(&mpCombinedMatrix[1]);
	//��
	mColSphereHead.Matrix(&mpCombinedMatrix[1]);
	//��
	mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);

}
