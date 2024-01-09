#pragma once

#include "CCollider.h"

//コライダタスククラス
class CColliderTask : public CTask
{
public:
	//コンストラクタ（コライダのポインタ）
	CColliderTask(CCollider* col);
	//コライダのポインタを取得
	CCollider* Collider();
	~CColliderTask();
private:
	//コライダへのポインタ
	CCollider* mpCollider;
};

//コライダリストクラス
class CColliderList {
public:
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask* task);
	//衝突処理
	void Collision(CCollider* task);
	//デフォルトコンストラクタ
	CColliderList();
private:
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
};

#define TASK_LINE 20	//リストをTASK_LINEで3次元に分散する
#define MAP_SIZE 100	//マップのおおよその大きさ

class CColliderManager
{
public:
	//インスタンスの取得
	static CColliderManager* Instance();

	//コライダの追加
	void Add(CCollider* col);
	//コライダの衝突処理
	void Collision(CCollider* col);

	//コライダタスクの削除
	void Remove(CCollider* col);

private:
	//エリア毎のコライダリスト
	CColliderList mTM[TASK_LINE][TASK_LINE][TASK_LINE];
	//マネージャのインスタンス
	static CColliderManager* mpInstance;
};
