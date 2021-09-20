#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"
#include "CCollider.h"

#define COLLISIONRANGE 30 //衝突処理範囲より離れているコライダは衝突処理しない

class CCollisionManager : public CTaskManager
{
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;
public:
	//インスタンスの取得
	static CCollisionManager* Get();
	//衝突処理
	void Collision();
	void Collision(CCollider *collider, int range);
};

#endif
