#pragma once

#include "CCollider.h"

#define TASK_LINE 20	//リストをTASK_LINE*TASK_LINEで分散する
#define MAP_SIZE 100

class CColliderTask : public CTask
{
public:
	CColliderTask(CCollider* col);
	CCollider* Collider();
	~CColliderTask();
private:
	CCollider* mpCollider;
};

class CTaskManager2 {
public:
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask* task);
	//衝突処理
	void Collision(CCollider* task);
	//デフォルトコンストラクタ
	CTaskManager2();
	//
	//void Render();
protected:
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
};

class CCollisionManager2
{
public:
	//インスタンスの取得
	static CCollisionManager2* Instance();

	//コライダの追加
	void Add(CCollider* col);
	//コライダの削除
	void Delete(CCollider* col);
	//コライダの衝突処理
	void Collision(CCollider* col);

	//コライダタスクの削除
	void Remove(CCollider* col);

private:
	CTaskManager2 mTM[TASK_LINE][TASK_LINE][TASK_LINE];
	//マネージャのインスタンス
	static CCollisionManager2* mpInstance;
};
