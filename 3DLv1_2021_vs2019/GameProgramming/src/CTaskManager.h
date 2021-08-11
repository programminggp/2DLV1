#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//タスククラスのインクルード
#include "CTask.h"

/*
タスクマネージャ
タスクリストの管理
*/
class CTaskManager {
public:
	//インスタンスの取得
	static CTaskManager* Get();
	//デストラクタ
	virtual ~CTaskManager();
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask *task);
	//更新
	void Update();
	//描画
	void Render();
	//リストから削除
	//Remove(タスクのポインタ)
	void Remove(CTask *task);
	//タスクの削除
	void Delete();
	//衝突処理
	void TaskCollision();
protected:
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
	//デフォルトコンストラクタ
	CTaskManager();
private:
	//タスクマネージャのインスタンス
	static CTaskManager* mpInstance;
};
//タスクマネージャyの外部参照
//extern CTaskManager TaskManager;

#endif
