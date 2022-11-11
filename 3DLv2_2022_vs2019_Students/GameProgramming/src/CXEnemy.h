#pragma once
#include "CXCharacter.h"
#include "CCollider.h"
#include "CColliderCapsule.h"

class CXEnemy : public CXCharacter
{
public:
	CXEnemy(const CVector& pos, const CVector& rot, CVector& scale);
	CXEnemy();
	void Init(CModelX* model);
	//Õ“Ëˆ—
	void Collision(CCollider* m, CCollider* o);
private:
	static CModelX mModel;
	//ƒRƒ‰ƒCƒ_‚ÌéŒ¾
	CColliderCapsule mColCapsBody;	//‘Ì
	CCollider mColSphereHead;	//“ª
	CCollider mColSphereSword0;	//Œ•
	CCollider mColSphereSword1;	//Œ•
	CCollider mColSphereSword2;	//Œ•
};