#include "CColliderManager.h"

//コライダの保持
CColliderTask::CColliderTask(CCollider* col)
	: mpCollider(col)
{
}

//コライダのポインタを返す
CCollider* CColliderTask::Collider()
{
	return mpCollider;
}

//リストから削除
CColliderTask::~CColliderTask()
{
	//前のタスクの次を、次のタスクにする
	mpPrev->mpNext = mpNext;
	//次のタスクの前を、前のタスクにする
	mpNext->mpPrev = mpPrev;
}


/////////////////////////////////////////////
//CColliderList

CColliderList::CColliderList()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

//リストに追加
//Add(タスクのポインタ)
void CColliderList::Add(CTask* addTask)
{
	CTask* task = &mTail;
	//addTaskの次をtask
	addTask->mpNext = task;
	//addTaskの前をtaskの前に
	addTask->mpPrev = task->mpPrev;
	//addTaskの前の次をaddTaskに
	addTask->mpPrev->mpNext = addTask;
	//taskの前をaddTaskに
	task->mpPrev = addTask;
}

void CColliderList::Collision(CCollider* task)
{
	//現在位置を先頭にする
	CColliderTask* next = (CColliderTask*)mHead.mpNext;
	//最後まできたら終了する
	//次が0になったら終了
	while (next->mpNext) {
		//親の衝突処理を呼び出す
		//自分の衝突処理
		if (task->Parent() != next->Collider()->Parent())
			if (task->Parent() && task != next->Collider())
				task->Parent()->Collision(task, next->Collider());
		//次を求める
		next = (CColliderTask*)next->mpNext;
	}
}


//マネージャのインスタンス
CColliderManager* CColliderManager::mpInstance = nullptr;
//インスタンスの取得
CColliderManager* CColliderManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CColliderManager();
	}
	return mpInstance;
}

void CColliderManager::Add(CCollider* col)
{
	//中心座標からエリアを求める
	int y = (int)(col->mCenter.Y() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	int x = (int)(col->mCenter.X() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);

	//隣接エリアを求める
	int ys = y - 1;
	int ye = y + 1;
	int xs = x - 1;
	int xe = x + 1;
	int zs = z - 1;
	int ze = z + 1;
	//添え字の範囲内におさめる
	if (ys < 0) ys = 0;
	if (ye >= TASK_LINE) ye = TASK_LINE - 1;
	if (xs < 0) xs = 0;
	if (xe >= TASK_LINE) xe = TASK_LINE - 1;
	if (zs < 0) zs = 0;
	if (ze >= TASK_LINE) ze = TASK_LINE - 1;
	//コライダタスクを生成しリストに追加する
	int i = 0;
	for (y = ys; y <= ye; ++y)
	{
		for (x = xs; x <= xe; ++x)
		{
			for (z = zs; z <= ze; ++z)
			{
				col->mpColliderTask[i] = new CColliderTask(col);
				mTM[y][x][z].Add(
					(CTask*)col->mpColliderTask[i++]);
			}
		}
	}
}

void CColliderManager::Remove(CCollider* col)
{
	//コライダにあるコライダタスクを全て削除
	for (int i = 0; i < COLLIDERTASK_SIZE; ++i)
	{
		if (col->mpColliderTask[i] != nullptr)
		{
			delete col->mpColliderTask[i];
			col->mpColliderTask[i] = nullptr;
		}
	}
}

void CColliderManager::Collision(CCollider* col)
{
	//当該エリアを求め、コライダリストの衝突処理を呼ぶ
	int y = (int)(col->mCenter.Y() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	int x = (int)(col->mCenter.X() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	if (y < 0) y = 0;
	if (y >= TASK_LINE) y = TASK_LINE - 1;
	if (x < 0) x = 0;
	if (x >= TASK_LINE) x = TASK_LINE - 1;
	if (z < 0) z = 0;
	if (z >= TASK_LINE) z = TASK_LINE - 1;
	mTM[y][x][z].Collision(col);
}

