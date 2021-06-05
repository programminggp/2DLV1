#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollision.h"
#include "CBillBoard.h"

class CXEnemy : public CXCharacter {
public:
	CEffectHit mBillBorad;
	//25
	//コライダの宣言
	CSphereCollider *mpColSphereBody;
	CSphereCollider *mpColSphereHead;
	CSphereCollider *mpColSphereSword;
	//31
	CXCharacter *mpPlayer;	//プレイヤーポインタ
	//見失った時の回転に使用
	float radian;
	//コライダの初期化
	CXEnemy()
		: mpColSphereBody(0)
		, mpColSphereHead(0)
		, mpColSphereSword(0)
		//31
		, mpPlayer(0)
		, radian(0.0f)
	{
		mTag = EENEMY;	//27 タグに敵設定
	}
	//36
	CXEnemy(CModelX *m, CVector3 pos)
		: CXEnemy() {
		Init(m); //初期化処理
		mPosition = pos; //位置設定
		//Taskマネージャに追加
		CTaskManager::Get()->Add(this);
	}

	~CXEnemy() {
		//コライダの削除
		//35 削除の削除
		//if (mpColSphereBody)
		//	delete mpColSphereBody;
		//mpColSphereBody = 0;
		//if (mpColSphereHead)
		//	delete mpColSphereHead;
		//mpColSphereHead = 0;
		//if (mpColSphereSword)
		//	delete mpColSphereSword;
		//mpColSphereSword = 0;
	}

	void Init(CModelX*);
	void Update();
	//27 衝突処理
	bool Collision(CCollider *m, CCollider *y);
};

#endif
