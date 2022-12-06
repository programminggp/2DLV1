#include "CPaladin.h"
#include "CKey.h"
#include "CCollisionManager.h"
#include "CActionCamera.h"
#include "CUtil.h"
#include "CSceneTest.h"

#include "CEffect.h"

#define GRAVITY  CVector(0.0f,-0.01f,0.0f)

void CPaladin::Render()
{
	CXCharacter::Render();
	CUtil::Start2D(0.0f, 800.0f, 0.0f, 600.0f);
	CVector screen;
	if (CActionCamera::Instance()->WorldToScreen(&screen, Position()))
	{
		CSceneTest::Text()->DrawString("PALADIN", screen.X(), screen.Y(), 7, 14);
	}
	CUtil::End2D();
}

void CPaladin::Update()
{
	if (CKey::Push('W'))
	{
		mPosition = mPosition + mMatrixRotate.VectorZ() * 0.03f;
	}
	if (CKey::Push('D'))
	{
		mRotation.Y(mRotation.Y() - 1.0f);
	}
	if (CKey::Push('A'))
	{
		mRotation.Y(mRotation.Y() + 1.0f);
	}
	if (CKey::Once('1'))
	{
		new CEffectDarkness17(mPosition + CVector(0.0f, 2.0f, 0.0f), 6, 3, 5, 2, 2);
	}
	if (CKey::Once('2'))
	{
		new CEffectFire7(mPosition + CVector(0.0f, 2.0f, 0.0f), 4, 4, 6, 2, 2);
	}
	if (CKey::Once('3'))
	{
		new CEffectFire7(mPosition + CVector(0.0f, 1.0f, 0.0f), 2, 2, 6, 2, 10, CEffect::EFADE, 7);
	}
	if (CKey::Once('4'))
	{
		float x;
		float y;
		x = (rand() % 10 + 1) / 10.0f;
		y = (rand() % 10 + 1) / 10.0f;
		new CEffectFire7(mPosition + CVector(0.0f + x, 1.0f + y, 0.0f), 2, 2, 6, 2, 10, CEffect::EFADE, 7);
		x = (rand() % 10 + 1) / 10.0f;
		y = (rand() % 10 + 1) / 10.0f;
		new CEffectFire7(mPosition + CVector(0.0f + x, 1.0f + y, 0.0f), 2, 2, 6, 2, 10, CEffect::EFADE, 7);
		x = (rand() % 10 + 1) / 10.0f;
		y = (rand() % 10 + 1) / 10.0f;
		new CEffectFire7(mPosition + CVector(0.0f + x, 1.0f + y, 0.0f), 2, 2, 6, 2, 10, CEffect::EFADE, 7);
		x = (rand() % 10 + 1) / 10.0f;
		y = (rand() % 10 + 1) / 10.0f;
		new CEffectFire7(mPosition + CVector(0.0f + x, 1.0f + y, 0.0f), 2, 2, 6, 2, 10, CEffect::EFADE, 7);
		x = (rand() % 10 + 1) / 10.0f;
		y = (rand() % 10 + 1) / 10.0f;
		new CEffectFire7(mPosition + CVector(0.0f + x, 1.0f + y, 0.0f), 2, 2, 6, 2, 10, CEffect::EFADE, 7);
	}
	mPosition = mPosition + GRAVITY;
	CXCharacter::Update();
}

CPaladin::CPaladin(CVector pos, CVector rot, CVector scale)
	: mColCapsule(this,nullptr, CVector(0.0f, 170.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), 0.4f)
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
}

void CPaladin::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//‡¬s—ñ‚ÌÝ’è
	mColCapsule.Matrix(&mpCombinedMatrix[2]);
}

void CPaladin::TaskCollision()
{
	mColCapsule.ChangePriority();
	CCollisionManager::Get()->Collision(&mColCapsule, 30.0f);
}

void CPaladin::Collision(CCollider* m, CCollider* o)
{
	CVector adjust;
	switch(o->Type())
	{
	case CCollider::ECAPSUL:
		if (CCollider::CollisionCapsule(m, o, &adjust))
		{
			mPosition = mPosition + adjust;
		}
		break;
	case CCollider::ETRIANGLE:
		if (CCollider::CollisionTriangleLine(o, m,&adjust))
		{
			mPosition = mPosition + adjust;
		}
		break;
	}
}
