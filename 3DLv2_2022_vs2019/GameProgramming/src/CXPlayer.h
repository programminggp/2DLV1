#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CColliderLine.h"
#include "CColliderTriangle.h"
#include "CColliderCapsule.h"

class CXPlayer : public CXCharacter
{
	static CCharacter* spInstance;
	static CModelX mModel;
	float mJumpV;
	CVector mMove;

	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
	CCollider mColSphereSword0;	//剣
	CCollider mColSphereSword1;	//剣
	CCollider mColSphereSword2;	//剣
//	CColliderLine mColLine;
	CColliderCapsule mColLine;

public:
	CXPlayer();
	CXPlayer(const CVector& pos, const CVector& rot, const CVector& scale);

	/*
	初期化(Xモデルクラスのポインタ)
	*/
	//void Init(CModelX* model);

	void Update();

	void TaskCollision();

	void Collision(CCollider* m, CCollider* o);

	void Idle();
	void Walk();
	void Attack();
	void Jump();
	void ChangeState(EState state);
};

#endif
