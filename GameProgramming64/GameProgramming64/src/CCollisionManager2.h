#pragma once

#include "CCollider.h"

#define TASK_LINE 20	//リストをTASK_LINE*TASK_LINEで分散する
#define MAP_SIZE 200

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
	void Render();
protected:
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
};

class CCollisionManager2
{
public:
	//インスタンスの取得
	static CCollisionManager2* Instance();

	//タスクリストの取得
	CTaskManager2* TM(const CCollider* col);

	void Add(CCollider* col);
	void Remove(CColliderTask* col);
	void Delete(CCollider* col);

private:
	CTaskManager2 mTM[TASK_LINE][TASK_LINE][TASK_LINE];
	//マネージャのインスタンス
	static CCollisionManager2* mpInstance;
};
