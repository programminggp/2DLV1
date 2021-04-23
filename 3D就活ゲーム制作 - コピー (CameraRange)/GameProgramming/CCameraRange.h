#ifndef CCAMERARANGE_H
#define CCAMERARANGE_H
#include "CCharacter.h"
#include "CCollider.h"
#include "CCollisionManager.h"

class CCameraRange :public CCharacter{
public:
	static CCameraRange*mpCameraRange;
	//デフォルトコンストラクタ
	CCameraRange();

	//更新
	void Update();

	//カメラの当たり判定
	CCollider mColRange;

	////衝突処理
	//void Collision(CCollider *mc, CCollider *yc);

	//コライダの更新
	void TaskCollision();
};


#endif