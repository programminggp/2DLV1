#include "CXEnemy.h"
#include"CXCharacter.h"
#include"CCollisionManager.h"

CXEnemy::CXEnemy()
	/*: mColSphereBody(this, nullptr, CVector(0.5f, -1.0f, 0.0f), 1.0f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 1.0f, 0.0f), 1.5f)
	, mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f)
	, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f)
	, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f)*/
{
	mTag = EENEMY;
}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	////‡¬s—ñÝ’è
	//mColSphereBody.Matrix(&mpCombinedMatrix[1]);
	////“ª
	//mColSphereHead.Matrix(&mpCombinedMatrix[1]);
	////Œ•
	//mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	//mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	//mColSphereSword2.Matrix(&mpCombinedMatrix[26]);
}

void CXEnemy::Collision(CCollider* m, CCollider* o)
{
	switch (o->Type()) {
	case CCollider::ESPHERE:
		if (o->Tag() == CCollider::ESWORD) {
			if (CCollider::Collision(m, o)) {

				CXEnemy::ChangeAnimation(11, false, 30);
			}
		}
		break;
	}
}

void CXEnemy::TaskCollision()
{
	/*mColSphereBody.ChangePriority();
	mColSphereHead.ChangePriority();
	mColSphereSword.ChangePriority();*/
	//CCollisionManager::Get()->Collision(&mColSphereBody, COLLISIONRANGE);
	//CCollisionManager::Get()->Collision(&mColSphereHead, COLLISIONRANGE);
	//CCollisionManager::Get()->Collision(&mColSphereSword0, COLLISIONRANGE);
	//CCollisionManager::Get()->Collision(&mColSphereSword1, COLLISIONRANGE);
	//CCollisionManager::Get()->Collision(&mColSphereSword2, COLLISIONRANGE);
}

void CXEnemy::Update()
{
	CXCharacter::Update();
}

