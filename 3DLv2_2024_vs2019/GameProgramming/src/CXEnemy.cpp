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
	mColSphereBody.Matrix(&mpCombinedMatrix[1]);
	//頭
	mColSphereHead.Matrix(&mpCombinedMatrix[1]);
	//剣
	mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);

}
