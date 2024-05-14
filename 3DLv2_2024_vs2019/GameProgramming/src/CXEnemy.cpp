#include "CXEnemy.h"

void CXEnemy::Collision(CCollider* m, CCollider* o)
{
	if (m->Type() == CCollider::EType::ESPHERE)
	{
		if (o->Type() == CCollider::EType::ESPHERE)
		{
			if (o->Tag() == CCollider::ETag::ESWORD)
			{
				if (m->Tag() == CCollider::ETag::EBODY)
				{
					if (CCollider::Collision(m, o))
					{
						ChangeAnimation(11, false, 30);
					}
				}
			}
		}
	}
}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//‡¬s—ñ‚Ìİ’è
	mColSphereBody.Matrix(&mpCombinedMatrix[8]);
	//“ª
	mColSphereHead.Matrix(&mpCombinedMatrix[11]);
	//Œ•
	mColSphereSword.Matrix(&mpCombinedMatrix[21]);
}
