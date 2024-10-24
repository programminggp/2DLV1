#include "CZombie.h"
#define MODEL_PATH "res\\WorldZombie\\world_war_zombie.x"
//追加のアニメーションセット
#define ANIMATION_WALK "res\\WorldZombie\\Zombie_Walk.fbx.x"
#define ANIMATION_HIT "res\\WorldZombie\\Zombie Reaction Hit.x"

CModelX CZombie::sModel;

CZombie::CZombie()
	: CXCharacter(CCharacter3::ETag::EENEMY)
	, mColBody(
		this, 
		nullptr, 
		CVector(0.0f, -70.0f, 0.0f),
		CVector(0.0f, 70.0f, 0.0f), 
		0.5f)
{
	if (sModel.IsLoaded() == false)
	{
		sModel.Load(MODEL_PATH);
		//アニメーションの追加
		sModel.AddAnimationSet(ANIMATION_WALK); //0
		sModel.AddAnimationSet(ANIMATION_HIT); //1
	}
	Init(&sModel);
	mColBody.Matrix(&mpCombinedMatrix[3]);
	mState = EState::EWALK;
}

CZombie::CZombie(const CVector& pos, const CVector& rot, const CVector& scale)
	: CZombie()
{
	Position(pos);
	Rotation(rot);
	Scale(scale);
}

void CZombie::Update()
{
	switch(mState)
	{
	case CCharacter3::EState::EHIT:
		Hit();
		break;
	default:
		ChangeAnimation(0, false, 243);
		break;
	}
	CXCharacter::Update();
	mColBody.Update();
}

void CZombie::Collision(CCollider* m, CCollider* o)
{
	CVector adjust;
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE:
		switch (o->Type())
		{
		case CCollider::EType::ECAPSULE:
			switch (o->ParentTag())
			{
			case CCharacter3::ETag::EPLAYER:
				if (o->ParentState() == CCharacter3::EState::EATTACK)
				{
					if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
					{
						if (mState != CCharacter3::EState::EHIT)
						{
							mState = CCharacter3::EState::EHIT;
							ChangeAnimation(1, false, 121);
							AnimationFrame(0.3f);
						}
					}
				}
			}
			break;
		}
		break;
	}
}

void CZombie::Hit()
{
	ChangeAnimation(1, false, 121);
	if (IsAnimationFinished())
	{
		mState = CCharacter3::EState::EWALK;
	}
}
