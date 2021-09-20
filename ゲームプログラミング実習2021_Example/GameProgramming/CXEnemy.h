#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy : public CXCharacter
{
	CCollider mColSphereSword0;	//剣
	CCollider mColSphereSword1;	//剣
	CCollider mColSphereSword2;	//剣
public:
	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
//	CCollider mColSphereSword;	//剣

	CXEnemy();
	/*
	初期化(Xモデルクラスのポインタ)
	*/
	void Init(CModelX* model);

	//衝突処理
	//m:自分のコライダ o:相手のコライダ
	void Collision(CCollider* m, CCollider* o);

};

#endif
