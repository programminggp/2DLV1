#include "CXEnemy.h"

CXEnemy::CXEnemy()
//M
: mColSphereBody(this, CVector(0.5f, -1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.0f)
, mColSphereHead(this, CVector(0.0f, 1.f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.5f)
, mColSphereSword0(this, CVector(0.7f, 3.5f, -0.2f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.5f )
, mColSphereSword1(this, CVector(0.5f, 2.5f, -0.2f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.5f )
, mColSphereSword2(this, CVector(0.3f, 1.5f, -0.2f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.5f )
{
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

void CXEnemy::Init(CModelX *model)
{
	CXCharacter::Init(model);
	//‡¬s—ñ‚ÌÝ’è
	//M
	mColSphereBody.mpCombinedMatrix = &mpCombinedMatrix[1];
	//“ª
	mColSphereHead.mpCombinedMatrix = &mpCombinedMatrix[1];
	//Œ•
	mColSphereSword0.mpCombinedMatrix = &mpCombinedMatrix[26];
	mColSphereSword1.mpCombinedMatrix = &mpCombinedMatrix[26];
	mColSphereSword2.mpCombinedMatrix = &mpCombinedMatrix[26];
}

void CXEnemy::Collision(CCollider *m, CCollider *y)
{
	switch (m->mType)
	{
	case CCollider::ESPHERE:
		switch (y->mType)
		{
		case CCollider::ESPHERE:
			if (CCollider::Collision(m, y))
			{
				switch (y->mpParent->mTag)
				{
				case EPLAYER:
					switch (y->mTag)
					{
					case CCollider::ESWORD:
						//M
						ChangeAnimation(11, false, 100);	//ƒ_ƒEƒ“
						break;
					}
					break;
				}
			}
			break;
		}
		break;
	}
}

