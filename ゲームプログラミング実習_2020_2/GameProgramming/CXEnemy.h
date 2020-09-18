#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy : public CXCharacter {
public:
	//ƒRƒ‰ƒCƒ_‚ÌéŒ¾
	CCollider mColSphereBody;	//‘Ì
	CCollider mColSphereHead;	//“ª
	//M
	CCollider mColSphereSword0;	//Œ•
	CCollider mColSphereSword1;	//Œ•
	CCollider mColSphereSword2;	//Œ•

	CXEnemy();
	void Init(CModelX *model);
	//Õ“Ëˆ—
	void Collision(CCollider *m, CCollider *y);
};

#endif
