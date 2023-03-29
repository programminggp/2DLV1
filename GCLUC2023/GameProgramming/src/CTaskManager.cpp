#include "CTaskManager.h"
#include "CCharacter.h"

CTaskManager* CTaskManager::spinstance = nullptr;

//コンストラクタ
CTaskManager::CTaskManager()
	:mhead(nullptr)
{

}

//デストラクタ
CTaskManager::~CTaskManager()
{
	CTask* next = mhead;
	while (next != nullptr)
	{
		CTask* deleteTask = next;
		next = next->mpnext;
		delete deleteTask;
	}
}

//インスタンスを取得
CTaskManager* CTaskManager::Instance()
{
	if (spinstance == nullptr)
	{
		spinstance = new CTaskManager;
	}
	return spinstance;
}

//インスタンスを破棄
void CTaskManager::ClearInstance()
{
	if (spinstance != nullptr)
	{
		delete spinstance;
		spinstance = nullptr;
	}
}

//リストに追加
void CTaskManager::Add(CTask* task)
{
	//リストにタスクがない時
	if (mhead == nullptr)
	{
		mhead = task;
	}
	else  //リストにすでにタスクが追加されている時
	{
		CTask* prev = nullptr;
		CTask* next = mhead;
		while (next != nullptr)
		{
			//優先度を比較
			if (next->mpriority < task->mpriority)
			{
				break;
			}
			prev = next;
			next = next->mpnext; //次のタスクへ
		}

		task->mpprev = prev;
		task->mpnext = next;
		if (prev != nullptr)
		{
			/*追加するタスクより優先度が高いタスクの
			mpnextに追加するタスクを設定*/
			prev->mpnext = task;
		}
		else
		{
			mhead = task;
		}
		if (next != nullptr)
		{
			next->mpprev = task;
		}
	}
}

//リストから削除
void CTaskManager::Remove(CTask* task)//task(取り除くタスク)
{
	//取り除くタスクが先頭の場合
	if (mhead == task)
	{
		mhead = task->mpnext;
	}
	//取り除くタスクの前後を接続する
	CTask* prev = task->mpprev;
	CTask* next = task->mpnext;
	if (prev != nullptr)
	{
		prev->mpnext = task->mpnext;
	}
	if (next != nullptr)
	{
		next->mpprev = task->mpprev;
	}

	//取り除くタスクの接続先は空にする
	task->mpprev = nullptr;
	task->mpnext = nullptr;
}

//タスクを削除
void CTaskManager::Delete(CTask* task)
{
	delete task;
}

//すべてのタスクを削除
void CTaskManager::AllDelete()
{
	CTask* next = mhead;
	CTask* gomi;
	while (next != nullptr)
	{
		gomi = next->mpnext;
		next->Delete();
		next = gomi;
	}
}

//描画処理
void CTaskManager::Render()
{
	CTask* next = mhead;
	while (next != nullptr)
	{
		next->Render();
		next = next->mpnext;
	}
}

//更新処理
void CTaskManager::Update()
{
	CTask* next = mhead;
	while (next != nullptr)
	{
		next->Update();
		next = next->mpnext;
	}
}

//衝突処理1
void CTaskManager::Collision()
{
	CTask* next = mhead;
	CTask* tugi;
	CTask* mae;
	while (next != nullptr)
	{
		tugi = next->mpnext;
		while (tugi != nullptr)
		{
			next->Collision(((CCharacter*)next),(CCharacter*)tugi);
			tugi = tugi->mpnext;
		}
		mae = next->mpprev;
		while (mae != nullptr)
		{
			next->Collision(((CCharacter*)next), (CCharacter*)mae);
			mae = mae->mpprev;
		}
		next = next->mpnext;
	}
}
