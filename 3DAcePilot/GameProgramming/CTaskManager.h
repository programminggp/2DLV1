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
	CTask *mpHead;	//先頭ポインタ
//	CTask *mpTail;	//最後ポインタ
	//デフォルトコンストラクタ
	CTaskManager();
	//デストラクタ
	virtual ~CTaskManager();
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask *task);
	//更新
	void Update();
	//描画
	void Render();
	//22
	//リストから削除
	//Remove(タスクのポインタ)
	void Remove(CTask *task);
	//22
	//タスクの削除
	void Delete();

	void ChangePriority(CTask *task, int priority);
};

//タスクマネージャyの外部参照
extern CTaskManager TaskManager;

#endif
