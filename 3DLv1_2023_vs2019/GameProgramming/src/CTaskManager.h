#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//タスククラスのインクルード
#include "CTask.h"
#include "CCollider.h"

//衝突処理範囲より離れているコライダは衝突処理しない
#define COLLISIONRANGE 30

/*
タスクマネージャ
タスクリストの管理
*/
class CTaskManager {
public:
	void Collision(CCollider* c, int range);

	//デフォルトコンストラクタ
	CTaskManager();
	void Collision();
	//タスクの削除
	void Delete();
	//リストから削除
	//Remove(タスクのポインタ)
	void Remove(CTask* task);
	//デストラクタ
	virtual ~CTaskManager();
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask* addTask);
	//更新
	void Update();
	//描画
	void Render();
protected:
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
};

#endif
