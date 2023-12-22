#include "CFelguard.h"
#include "CKey.h"
#include "CCollisionManager.h"

CModelX CFelguard::mModel;

#define MODEL "res\\felguard\\felguard-X.X"

CFelguard::CFelguard()
	:mColHit(this, &mMatrix,CVector(0.0f, 0.0f, 0.0f), 1.8f)
	, mColCapsule(this, &mMatrix, CVector(0.0f, -2.5f, 0.0f), CVector(0.0f, 2.5f, 0.0f))//, 1.2f)
{
	if (!mModel.IsLoaded())
	{
		mModel.Load(MODEL);
		mModel.SeparateAnimationSet(0, 0, 701, "ALL"); //1
		mModel.SeparateAnimationSet(1, 0, 100, "IDLE"); //2
		mModel.SeparateAnimationSet(1, 380, 420, "WALK");
		mModel.SeparateAnimationSet(1, 150, 200, "ATTACK1");
		mModel.SeparateAnimationSet(1, 470, 510, "DEATH1");
		mModel.SeparateAnimationSet(1, 425, 460, "RUN");
		mModel.SeparateAnimationSet(1, 200, 260, "ATTACK_IDLE");
		mModel.SeparateAnimationSet(1, 260, 350, "ATTACK3");
		mModel.SeparateAnimationSet(1, 520, 700, "DEATH2");
	}
	mPosition = CVector(104.0f, 10.0f, 100.0f);
	mRotation.Y(180.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	Init(&mModel);
	ChangeState(EIDLE);
	//合成行列の設定
	mColHit.Matrix(&mpCombinedMatrix[4]);
	mColCapsule.Matrix(&mpCombinedMatrix[2]);
}

void CFelguard::Update()
{
	EState state = EIDLE;
	switch (mState)
	{
	case EDAMAGE:
		state = EDAMAGE;
		if (mKnockBack.Length() < 0.1f)
		{
			state = EIDLE;
			mKnockBack = CVector();
		}
		else
		{
			mPosition = mPosition + mKnockBack * 0.5f;
			mKnockBack = mKnockBack * 0.8f;
		}
		break;
	default:
		if (CKey::Push('1'))
		{
			state = EIDLE;
		}
		if (CKey::Push('2'))
		{
			state = EWALK;
		}
		if (CKey::Push('3'))
		{
			state = EATTACK;
		}
		if (CKey::Push('4'))
		{
			state = EDEATH;
		}
		if (CKey::Push('5'))
		{
			state = EJUMP;
		}
	}
	CXCharacter::Update();
	ChangeState(state);
	mColCapsule.Update();
	mColHit.Update();
}

void CFelguard::ChangeState(EState state)
{
	if (mState == state) return;
	mState = state;
	switch (state)
	{
	case EIDLE:
		ChangeAnimation(EIDLE, true, 100);
		break;
	case EWALK:
		ChangeAnimation(EWALK, true, 40);
		break;
	case EATTACK:
		ChangeAnimation(EATTACK, false, 50);
		break;
	case EDEATH:
		ChangeAnimation(EDEATH, false, 40);
		break;	
	case EJUMP:
		ChangeAnimation(EJUMP, false, 55);
		break;
	case EDAMAGE:
		ChangeAnimation(EDEATH, false, 40);
		break;
	}
}

void CFelguard::TaskCollision()
{
	//CCollisionManager::Get()->Collision(&mColHit, 20);
	CCollisionManager2::Instance()->TM(&mColHit)->Collision(&mColHit);
}

void CFelguard::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::ECAPSUL:
		if (o->Type() == CCollider::ECAPSUL)
		{
			CVector ad;
			if (CCollider::CollisionCapsule(m, o, &ad))
			{
				//当たらない位置まで下がる
				mPosition = mPosition + ad;
			}
		}
		break;
	case CCollider::ESPHERE:
		//ダメージ処理
		//ダメージ中でない
		if (mState != EDAMAGE)
		{
			//球かつプレイヤーかつ攻撃かつ武器の時
			if (o->Type() == CCollider::ESPHERE
				&& o->Parent()->Tag() == EPLAYER
				&& o->Parent()->State() == EATTACK
				&& o->Tag() == CCollider::EWEAPON)
			{
				//当たればダメージ
				if (CCollider::Collision(o, m))
				{
					mKnockBack = (m->Parent()->Position() - o->Parent()->Position()).Normalize()
						* o->Parent()->AttackPower() ;
					ChangeState(EDAMAGE);
				}

			}
		}
		break;
	}
}