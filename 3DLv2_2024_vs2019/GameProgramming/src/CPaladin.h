#ifndef CPALADIN_H
#define CPALADIN_H

#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CInput.h"

class CPaladin : public CXCharacter
{
public:
	CPaladin();
	CPaladin(const CVector& pos, const CVector& rot, const CVector& scale);
	void Update();
	void Collision(CCollider* m, CCollider* o);
	void Collision();

private:
	void Jump();
	void Idle();
	void Walk();
	void Attack();
	CColliderCapsule mColBody;	//‘Ì
	CColliderCapsule mColSword;
	static CModelX sModel;
	CInput mInput;
};

#endif

