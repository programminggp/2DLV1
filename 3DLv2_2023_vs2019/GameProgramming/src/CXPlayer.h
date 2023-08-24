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
	//�R���C�_�̐錾
//	CCollider mColSphereBody;	//��
	CColliderCapsule mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword;	//��
	CInput mInput;
};

#endif