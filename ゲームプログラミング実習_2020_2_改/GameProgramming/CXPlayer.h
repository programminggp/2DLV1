#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer : public CXCharacter {
public:
	//ƒRƒ‰ƒCƒ_‚ÌéŒ¾
	CCollider mColSphereBody;	//‘Ì
	CCollider mColSphereHead;	//“ª
	CCollider mColSphereSword;	//Œ•

	CXPlayer();
	void Update();
	void Init(CModelX *model);
};

#endif
