#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"
#include "CCollider.h"

#define COLLISIONRANGE 30 //衝突処理範囲より離れているコライダは衝突処理しない

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

#define TASK_LINE 10

class CCollisionManager2
{
public:
	//インスタンスの取得
	static CCollisionManager2* Instance();
	//衝突処理
//	void Collision();
//	void Collision(CCollider* collider, int range);
	CTaskManager2* TM(const CCollider* col);
private:
	CTaskManager2 mTM[TASK_LINE];
	//マネージャのインスタンス
	static CCollisionManager2* mpInstance;
};

#endif
