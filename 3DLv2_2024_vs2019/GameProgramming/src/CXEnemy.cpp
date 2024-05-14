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
	//合成行列の設定
	mColSphereBody.Matrix(&mpCombinedMatrix[8]);
	//頭
	mColSphereHead.Matrix(&mpCombinedMatrix[11]);
	//剣
	mColSphereSword.Matrix(&mpCombinedMatrix[21]);
}
