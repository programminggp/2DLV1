#include "CCollisionManager.h"
//
#include "CCollider.h"

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
	CCollider *task = (CCollider*)mHead.mpNext;
	//最後まできたら終了する
	while (task->mpNext) {
		//現在位置の次を求める
		CCollider *next = (CCollider*)task->mpNext;
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
