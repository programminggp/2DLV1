#ifndef CXENEMYKNIGHT_H
#define CXENEMYKNIGHT_H

#include "CXCharacter.h"
#include "CCollision.h"
#include "CBillBoard.h"
#include "CHpBar.h"
#include "main.h"
#include <vector>

class CXEnemyKnight : public CXCharacter {
public:
	//コライダ
	std::vector<CCollider*> mColliders;

	CHPBar mHpBar;//HPゲージ

	CXCharacter *mpPlayer;	//プレイヤーポインタ
	//見失った時の回転に使用
	float radian;

	CXEnemyKnight()
		: mpPlayer(0)
		, radian(0.0f)
		, mHpBar(CVector3(), CVector2(30,2), 100, 100)
	{
		mTag = EENEMY;	//27 タグに敵設定
	}

	CXEnemyKnight(CModelX *m, CVector3 pos)
		: CXEnemyKnight() {
		Init(m); //初期化処理
		mPosition = pos; //位置設定
		//Taskマネージャに追加
		CTaskManager::Get()->Add(this);
	}

	~CXEnemyKnight() {
		for (int i = 0; i < mColliders.size(); i++) {
			CCollisionManager::Get()->Remove(mColliders[i]);
		}
		mColliders.clear();
	}

	void Init(CModelX*);
	void Update();
	bool Collision(CCollider *m, CCollider *y);
	void Render();
};

#endif
