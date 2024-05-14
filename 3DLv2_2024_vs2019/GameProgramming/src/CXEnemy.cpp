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
	//�����s��̐ݒ�
	mColSphereBody.Matrix(&mpCombinedMatrix[1]);
	//��
	mColSphereHead.Matrix(&mpCombinedMatrix[1]);
	//��
	mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);

}
