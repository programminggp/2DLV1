#include "CCollisionManager.h"
//
#include "CCollider.h"
#include "CColliderTriangle.h"
#include "CColliderLine.h"

//マネージャのインスタンス
CCollisionManager* CCollisionManager::mpInstance = 0;
//インスタンスの取得
CCollisionManager* CCollisionManager::Get()
{
	if (mpInstance == 0)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}

//衝突処理
void CCollisionManager::Collision() {
	//現在位置を先頭にする
	CCollider*task = (CCollider*)mHead.mpNext;
	//最後まできたら終了する
	while (task->mpNext) {
		//現在位置の次を求める
		CCollider*next = (CCollider*)task->mpNext;
		//次が0になったら終了
		while (next->mpNext) {
			//親の衝突処理を呼び出す
			//自分の衝突処理
			if (task->mpParent)
				task->mpParent->Collision(task, next);
			//相手の衝突処理
			if (next->mpParent)
				next->mpParent->Collision(next, task);
			//次を求める
			next = (CCollider*)next->mpNext;
		}
		//現在位置を次にする
		task = (CCollider*)task->mpNext;
	}
}
//衝突処理
//Collision(コライダ, 範囲)
//コライダの優先度+範囲～優先度-範囲までのコライダと衝突判定を実行する
void CCollisionManager::Collision(CCollider *c, int range) {
	//現在位置を先頭にする
	CCollider *task = (CCollider*)mHead.mpNext;
	//範囲まで読み飛ばし
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority + range)
		{
			break;
		}
		//現在位置を次にする
		task = (CCollider*)task->mpNext;
	}
	//最後まできたら終了する
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority - range)
		{
			break;
		}
		//親の衝突処理を呼び出す
		//自分の衝突処理
		if (c->mpParent && c != task)
			c->mpParent->Collision(c, task);
		//現在位置を次にする
		task = (CCollider*)task->mpNext;
	}
}

//マネージャのインスタンス
CCollisionManager2* CCollisionManager2::mpInstance = 0;
//インスタンスの取得
CCollisionManager2* CCollisionManager2::Instance()
{
	if (mpInstance == 0)
	{
		mpInstance = new CCollisionManager2();
	}
	return mpInstance;
}

CTaskManager2* CCollisionManager2::TM(const CCollider* col)
{
//	return &mTM[col->mPriority % TASK_LINE];
	int x = (int)(col->mCenter.X()) % 100 / (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z()) % 100 / (100 / TASK_LINE);
	return &mTM[x][z];
}

void CCollisionManager2::Add(CCollider* col)
{
	int x = (int)(col->mCenter.X()) % 100 / (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z()) % 100 / (100 / TASK_LINE);
	int sx = x - 1;
	int ex = x + 1;
	int sz = z - 1;
	int ez = z + 1;
	if (sx < 0) sx = 0;
	if (ex >= TASK_LINE) ex = TASK_LINE - 1;
	if (sz < 0) sz = 0;
	if (ez >= TASK_LINE) ez = TASK_LINE - 1;
	int i = 0;
	for (x = sx; x <= ex; ++x)
	{
		for (z = sz; z <= ez; ++z)
		{
			col->mpColliderTask[i] = new CColliderTask(col);
			mTM[x][z].Add((CTask*)col->mpColliderTask[i++]);
			//switch (col->Type())
			//{
			//case CCollider::EType::ESPHERE:
			//	col->mpSubCollider[i] = new CCollider(false);
			//	*(col->mpSubCollider[i]) = *(CCollider*)col;
			//	mTM[x][z].Add((CTask*)col->mpSubCollider[i++]);
			//	break;
			//case CCollider::EType::ELINE:
			//	col->mpSubCollider[i] = new CColliderLine(false);
			//	*(col->mpSubCollider[i]) = *(CColliderLine*)col;
			//	mTM[x][z].Add((CTask*)col->mpSubCollider[i++]);
			//	break;
			//case CCollider::EType::ETRIANGLE:
			//	col->mpSubCollider[i] = new CColliderTriangle(false);
			//	*(col->mpSubCollider[i]) = *(CColliderTriangle*)col;
			//	mTM[x][z].Add((CTask*)col->mpSubCollider[i++]);
			//	break;
			//}
		}
	}
	//mTM[x][z].Add((CTask*)col);
}

void CCollisionManager2::Remove(CColliderTask* col)
{
	//タスクの前の次を、タスクの次にする
	col->mpPrev->mpNext = col->mpNext;
	//タスクの次の前を、タスクの前にする
	col->mpNext->mpPrev = col->mpPrev;
	return;
	int x = (int)(col->Collider()->mCenter.X()) % 100 / (100 / TASK_LINE);
	int z = (int)(col->Collider()->mCenter.Z()) % 100 / (100 / TASK_LINE);
	int sx = x - 1;
	int ex = x + 1;
	int sz = z - 1;
	int ez = z + 1;
	if (sx < 0) sx = 0;
	if (ex >= TASK_LINE) ex = TASK_LINE - 1;
	if (sz < 0) sz = 0;
	if (ez >= TASK_LINE) ez = TASK_LINE - 1;
	int i = 0;
	for (x = sx; x <= ex; ++x)
	{
		for (z = sz; z <= ez; ++z)
		{
			if (col != nullptr)
			{
				mTM[x][z].Remove((CTask*)col);
			}
		}
	}
	//mTM[x][z].Remove((CTask*)col);
}

void CCollisionManager2::Delete(CCollider* col)
{
	for (int i = 0; i < 9; ++i)
	{
		if (col->mpColliderTask[i] != nullptr)
		{
			delete col->mpColliderTask[i];
			col->mpColliderTask[i] = nullptr;
		}
	}
}
