#include "CXEnemy.h"

CXEnemy::CXEnemy()
: mColSphereBody(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.5f)
, mColSphereHead(this, CVector(0.0f, 5.0f, -3.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.5f)
, mColSphereSword(this, CVector(-10.0f, 10.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.3f)
{
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

void CXEnemy::Init(CModelX *model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpCombinedMatrix = &mpCombinedMatrix[8];
	//頭
	mColSphereHead.mpCombinedMatrix = &mpCombinedMatrix[11];
	//剣
	mColSphereSword.mpCombinedMatrix = &mpCombinedMatrix[21];
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
						ChangeAnimation(11, false, 30);	//ダウン
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

