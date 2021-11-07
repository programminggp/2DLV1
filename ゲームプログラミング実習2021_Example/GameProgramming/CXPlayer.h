#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CColliderLine.h"
#include "CColliderTriangle.h"

class CXPlayer : public CXCharacter
{
	float mJumpV;
	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
	CCollider mColSphereSword;	//剣
	CColliderLine mColLine;
#ifdef _DEBUG
	CColliderTriangle mColDummy1;
	CColliderTriangle mColDummy2;
#endif
public:
	static CCharacter* spInstance;
	CXPlayer();
	CXPlayer(const CVector& pos, const CVector& rot, const CVector& scale);

	/*
	初期化(Xモデルクラスのポインタ)
	*/
	void Init(CModelX* model);

	void Update();

	void TaskCollision();

	void Collision(CCollider* m, CCollider* o);
};

#endif
