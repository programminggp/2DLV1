#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"

#include "CInput.h"

#include "CCollider.h"
#include "CColliderCapsule.h"

class CXPlayer : public CXCharacter
{
public:
	void CXPlayer::Collision(CCollider* m, CCollider* o)
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
		}
	}

	void Init(CModelX* model);
	//コライダの初期化
	CXPlayer()
		: 
		mColBody(this, nullptr, CVector(0.0f, 25.0f, 0.0f),
			CVector(0.0f, 150.0f, 0.0f), 0.5f)
		, mColSphereBody(this, nullptr, CVector(), 0.5f)
		, mColSphereHead(this, nullptr,
			CVector(0.0f, 5.0f, -3.0f), 0.5f)
		, mColSphereSword(this, nullptr,
			CVector(-10.0f, 10.0f, 50.0f), 0.3f, CCollider::ETag::ESWORD)

	{
	}
	void Update();
private:
	CColliderCapsule mColBody;	//体

	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
	CCollider mColSphereSword;	//剣

	CInput mInput;
};


#endif

