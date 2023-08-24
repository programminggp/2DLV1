#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CColliderCapsule.h"

class CXEnemy : public CXCharacter
{
public:
	//Õ“Ëˆ—
	void Collision(CCollider* m, CCollider* o);
	CXEnemy();
	void Init(CModelX* model);
private:
	//ƒRƒ‰ƒCƒ_‚ÌéŒ¾
	CColliderCapsule mColBody;	//‘Ì
	CCollider mColSphereBody;	//‘Ì
	CCollider mColSphereHead;	//“ª
	CCollider mColSphereSword0;	//Œ•
	CCollider mColSphereSword1;	//Œ•
	CCollider mColSphereSword2;	//Œ•
};


#endif
