#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"
#include "CCollider.h"

#define COLLISIONRANGE 10 //衝突処理範囲より離れているコライダは衝突処理しない

class CCollisionManager : public CTaskManager
{
public:
	//インスタンスの取得
	static CCollisionManager* Get();
	//衝突処理
	void Collision();
	void Collision(CCollider *collider, int range);
private:
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;
};

#endif
