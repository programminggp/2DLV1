#include "CXEnemy.h"

void CXEnemy::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE:
		if (o->Type() == CCollider::EType::ECAPSULE)
		{
			CVector adjust;
			if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
			{
				mPosition = mPosition + adjust;
				CTransform::Update();
			}
		}
		break;

	case CCollider::EType::ESPHERE:
		if (o->Type() == CCollider::EType::ESPHERE)
		{
			if (o->Tag() == CCollider::ETag::ESWORD)
			{
				if (m->Tag() == CCollider::ETag::EBODY)
				{
					if (CCollider::Collision(m, o))
					{
						//ChangeAnimation(11, false, 30);
					}
				}
			}
		}
		break;
	}
}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//‡¬s—ñ‚Ìİ’è
	mColSphereBody.Matrix(&mpCombinedMatrix[1]);
	//“ª
	mColSphereHead.Matrix(&mpCombinedMatrix[1]);
	//Œ•
	mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);
	mColBody.Matrix(&mpCombinedMatrix[1]);
}
