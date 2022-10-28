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
	void Collision();
	//インスタンスの取得
	static CTaskManager* Instance();
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
	//デフォルトコンストラクタ
	CTaskManager();
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
private:
	//タスクマネージャのインスタンス
	static CTaskManager* mpInstance;
};

#endif
