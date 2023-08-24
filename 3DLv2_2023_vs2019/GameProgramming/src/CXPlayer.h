#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CInput.h"
#include "CColliderCapsule.h"

class CXPlayer : public CXCharacter
{
public:
	CXPlayer();
	void Init(CModelX* model);
	void Update();
	void Collision(CCollider* m, CCollider* o);
private:
	//ƒRƒ‰ƒCƒ_‚ÌéŒ¾
//	CCollider mColSphereBody;	//‘Ì
	CColliderCapsule mColSphereBody;	//‘Ì
	CCollider mColSphereHead;	//“ª
	CCollider mColSphereSword;	//Œ•
	CInput mInput;
};

#endif