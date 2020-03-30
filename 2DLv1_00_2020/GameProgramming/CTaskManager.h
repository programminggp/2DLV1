#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H

//タスククラスインクルード
#include"CTask.h"

//タスクマネージャの外部参照

/*
タスクマネージャ
タスクリスト管理
*/
class CTaskManager{
public:
	CTask *mpHead;//先頭ポイント
	CTask *mpRHead;//先頭ポイント

	//デフォルトコンストラクタ
	CTaskManager();

	//デストラクタ
	virtual~CTaskManager();

	//リストから消去
	void Remove(CTask*task);
	void RemoveR(CTask*task);

	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask *task, int priority, int priorityr);
	void Add(CTask *task);
	void AddR(CTask *task);

	void Collision();

	void AllDisable();
	//更新
	void Update();

	//描画
	void Render();

	////消去の確認
	//void DeleteCheck();

	//タスク消去
	void Delete();

	//タスクの優先度の変更
	void Changepriority(CTask*task,int priority);

	//タスク全消去
	void AllDelete();

};

extern CTaskManager TaskManager;

#endif