#pragma once
#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer : public CXCharacter
{
public:
	void Init(CModelX* model);
	CXPlayer();
	void Update();
private:
	//ƒRƒ‰ƒCƒ_‚ÌéŒ¾
	CCollider mColSphereBody;	//‘Ì
	CCollider mColSphereHead;	//“ª
	CCollider mColSphereSword;	//Œ•

};