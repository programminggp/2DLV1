#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//タスククラスのインクルード
#include"CTask.h"

/*
* タスクマネージャ
* タスクリストの管理
*/
class CTaskManager{
public:
	//インスタンスの取得
	static CTaskManager* Get();
	
	//デストラクタ
	virtual ~CTaskManager();
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask* addTask);
	//更新
	void Update();
	//描画
	void Render();
	//リストからの削除
	//Remove(タスクのポインタ)
	void Remove(CTask* task);
	//タスクの削除
	void Delete();

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

