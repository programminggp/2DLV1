#include <stdio.h>
#include "CTask.h"
//27
#include "CCollision.h"

//シングルトン　唯一のインスタンス
CCollisionManager *CCollisionManager::sInstance = 0;

bool CTask::mShadowMap = false; //シャドウマップ　true:マップ作成中

CCollisionManager* CCollisionManager::Get() {
	if (!sInstance) {
		//インスタンスが無い場合は生成
		sInstance = new CCollisionManager();
	}
	return sInstance;
}
/*
Add
コライダのリストに追加する
優先度は大きい値が先
*/
#define MGN 5.0f
void CCollisionManager::Add(CTask *task) {
	mCount++;
	if (((CCollider*)task)->mColParts < CCollider::ENONE) {
		int index = GetIndex(((CCollider*)task)->mPosition);
		if (0 <= index && index < COLROW * COLROW) {
			mCollisionList[index].Add((CCollider*)task);
		}
		else {
			printf("Index:%d", index);
		}
		//if (((CCollider*)task)->mPosition.x > -MGN) {
		//	if (((CCollider*)task)->mPosition.z > -MGN) {
		//		mCollisionList[EXPZP].Add((CCollider*)task);
		//	}
		//	if (((CCollider*)task)->mPosition.z < MGN) {
		//		mCollisionList[EXPZM].Add((CCollider*)task);
		//	}
		//}
		//if (((CCollider*)task)->mPosition.x < MGN) {
		//	if (((CCollider*)task)->mPosition.z > -MGN) {
		//		mCollisionList[EXMZP].Add((CCollider*)task);
		//	}
		//	if (((CCollider*)task)->mPosition.z < MGN) {
		//		mCollisionList[EXMZM].Add((CCollider*)task);
		//	}
		//}
	}
	if (mpHead) {
		//2件目以降の処理
		//カレントcに先頭を代入する
		CTask *c = mpHead;
		//先頭に追加の場合
		if (task->mPriority >= c->mPriority) {
			//先頭は引数のタスク
			mpHead = task;
			//先頭の前はなし
			task->mpPrev = 0;
			//先頭の次は、カレントc
			task->mpNext = c;
			//次の前は引数のタスク
			c->mpPrev = task;
//			return;
		} //先頭に追加の終わり
		else {
			c = c->mpNext;
			//先頭以降に追加
			while (c) {
				if (task->mPriority >= c->mPriority) {
					//カレントの前の次を引数のタスクにする
					c->mpPrev->mpNext = task;
					//引数のタスクの前をカレントの前に
					task->mpPrev = c->mpPrev;
					//引数のタスクの次をカレントに
					task->mpNext = c;
					//カレントの前を引数のタスクに
					c->mpPrev = task;
					break;
				}
				c = c->mpNext;
			} //途中に追加終了
			if (!c) {
				//最後に追加
				//最後の次を引数のタスクにする
				mpTail->mpNext = task;
				//引数のタスクの前を、今の最後にする
				task->mpPrev = mpTail;
				//引数のタスクの次を0にする
				task->mpNext = 0;
				//最後に引数のタスクを代入する
				mpTail = task;
			}
		}
	}
	else {	//0は偽
		//1件目の処理
		//先頭を引数のタスクにする
		mpHead = task;
		//先頭の前を0にする
		task->mpPrev = 0;
		//先頭の次を0にする
		task->mpNext = 0;
		//最後に引数のタスクを代入する
		mpTail = task;
	}
	return;
}

void CCollisionList::Add(CCollider *t) {
	mCount++;
	CCollider *task = new CCollider();
	*task = *t;
	if (mpHead) {
		//2件目以降の処理
		//カレントcに先頭を代入する
		CTask *c = mpHead;
		//先頭に追加の場合
		if (task->mPriority >= c->mPriority) {
			//先頭は引数のタスク
			mpHead = task;
			//先頭の前はなし
			task->mpPrev = 0;
			//先頭の次は、カレントc
			task->mpNext = c;
			//次の前は引数のタスク
			c->mpPrev = task;
			return;
		} //先頭に追加の終わり
		c = c->mpNext;
		//先頭以降に追加
		while (c) {
			if (task->mPriority >= c->mPriority) {
				//カレントの前の次を引数のタスクにする
				c->mpPrev->mpNext = task;
				//引数のタスクの前をカレントの前に
				task->mpPrev = c->mpPrev;
				//引数のタスクの次をカレントに
				task->mpNext = c;
				//カレントの前を引数のタスクに
				c->mpPrev = task;
				return;
			}
			c = c->mpNext;
		} //途中に追加終了
		//最後に追加
		//最後の次を引数のタスクにする
		mpTail->mpNext = task;
		//引数のタスクの前を、今の最後にする
		task->mpPrev = mpTail;
		//引数のタスクの次を0にする
		task->mpNext = 0;
		//最後に引数のタスクを代入する
		mpTail = task;
	}
	else {	//0は偽
		//1件目の処理
		//先頭を引数のタスクにする
		mpHead = task;
		//先頭の前を0にする
		task->mpPrev = 0;
		//先頭の次を0にする
		task->mpNext = 0;
		//最後に引数のタスクを代入する
		mpTail = task;
	}
}

/*27
Update
コリジョンの衝突処理
*/
void CCollisionManager::Update(){
	//カレントcを先頭にする
	CCollider *c = (CCollider*)mpHead;
	//カレントcが0になったら終了
	while (c && c->mPriority >= CCollider::ENONE) {
//	while (c && c->mpParent) {
		if (c->mpParent) {
			int index = GetIndex(((CCollider*)c)->mpParent->mPosition);
			mCollisionList[index - COLROW - 1].Update(c);
			mCollisionList[index - COLROW].Update(c);
			mCollisionList[index - COLROW + 1].Update(c);
			mCollisionList[index - 1].Update(c);
			mCollisionList[index].Update(c);
			mCollisionList[index + 1].Update(c);
			mCollisionList[index + COLROW - 1].Update(c);
			mCollisionList[index + COLROW].Update(c);
			mCollisionList[index + COLROW + 1].Update(c);
		}
		//コライダの種類判定
		switch (c->mTag) {
		case CCollider::ECOLSPHERE://球コライダの時
		{//29
			//先頭から衝突判定
			CCollider *y = (CCollider*)mpHead;
			//ワールド座標の球コライダを得る
			CSphereCollider m = ((CSphereCollider*)c)->GetWorld();
			while (y && y->mPriority >= CCollider::ENONE) {
//			while (y) {
				//同じ親のコライダはスキップ
				if (y->mpParent != c->mpParent) {
					//親の衝突判定を呼ぶ
					m.mpParent->Collision(&m, y);
				}
				//次の相手へ
				y = (CCollider*)y->mpNext;
			}
		}//29
			break;//29
			//29
		case CCollider::ECOLCAPSULE://カプセルコライダの時
		{
			//先頭から衝突判定
			CCollider *y = (CCollider*)mpHead;
			//ワールド座標の球コライダを得る
			CCapsuleCollider m = ((CCapsuleCollider*)c)->GetWorld();
			while (y && y->mPriority >= CCollider::ENONE) {
//			while (y) {
				//同じ親のコライダはスキップ
				if (y->mpParent != c->mpParent) {
					//親の衝突判定を呼ぶ
					m.mpParent->Collision(&m, y);
				}
				//次の相手へ
				y = (CCollider*)y->mpNext;
			}
		}
			break;
		}
#ifdef _DEBUG
		//カレントcを描画
//		c->Render();
#endif
		//カレントを次へ
		c = (CCollider*)c->mpNext;
	}
}

void CCollisionList::Update(CCollider *c){
	//カレントcを先頭にする
//	CCollider *c = (CCollider*)mpHead;
	//カレントcが0になったら終了
	while(c && c->mPriority >= CCollider::ENONE) {
		//コライダの種類判定
		switch (c->mTag) {
		case CCollider::ECOLSPHERE://球コライダの時
			{//29
				//先頭から衝突判定
				CCollider *y = (CCollider*)mpHead;
				//ワールド座標の球コライダを得る
				CSphereCollider m = ((CSphereCollider*)c)->GetWorld();
				while (y) {
					//同じ親のコライダはスキップ
					if (y->mpParent != c->mpParent) {
						//親の衝突判定を呼ぶ
						m.mpParent->Collision(&m, y);
					}
					//次の相手へ
					y = (CCollider*)y->mpNext;
				}
			}//29
			break;//29
		//29
		case CCollider::ECOLCAPSULE://カプセルコライダの時
			{
				//先頭から衝突判定
				CCollider *y = (CCollider*)mpHead;
				//ワールド座標の球コライダを得る
				CCapsuleCollider m = ((CCapsuleCollider*)c)->GetWorld();
				while (y) {
					//同じ親のコライダはスキップ
					if (y->mpParent != c->mpParent) {
						//親の衝突判定を呼ぶ
						m.mpParent->Collision(&m, y);
					}
					//次の相手へ
					y = (CCollider*)y->mpNext;
				}
			}
			break;
		}
#ifdef _DEBUG
		//カレントcを描画
		c->Render();
#endif
		//カレントを次へ
		c = (CCollider*)c->mpNext;
	}
}

/*35
Destory
リストを全て削除し、
自身も削除する
*/
void CCollisionManager::Destroy(){
	for (int i = 0; i < COLROW * COLROW; i++) {
		mCollisionList[i].Destroy();
	}
	//mCollisionList[1].Destroy();
	//mCollisionList[2].Destroy();
	//mCollisionList[3].Destroy();
	//カレントcを先頭にする
	CTask *c = mpHead;
	//カレントが0になったら終了
	while (c) {
		//カレントを次にする
		c = c->mpNext;
		//先頭を削除
		delete mpHead;
		//先頭にカレントを代入する
		mpHead = c;
	}
	//最後を0にする
	mpTail = 0;
	//自分自身を削除
	if (sInstance)
		delete sInstance;
	sInstance = 0;
}

void CCollisionList::Destroy(){
#ifdef _DEBUG
	printf("CollisionList:%d\n", mCount);
#endif
	//カレントcを先頭にする
	CTask *c = mpHead;
	//カレントが0になったら終了
	while (c) {
		//カレントを次にする
		c = c->mpNext;
		//先頭を削除
		delete mpHead;
		//先頭にカレントを代入する
		mpHead = c;
	}
	//最後を0にする
	mpTail = 0;
}

//シングルトン　唯一のインスタンス
CTaskManager *CTaskManager::sInstance = 0;

CTaskManager* CTaskManager::Get() {
	if (!sInstance) {
		//インスタンスが無い場合は生成
		sInstance = new CTaskManager();
	}
	return sInstance;
}
/*
Add
リストに追加する
優先度は大きい値が先
*/
void CTaskManager::Add(CTask *task) {
	if (mpHead) {
		//2件目以降の処理
		//カレントcに先頭を代入する
		CTask *c = mpHead;
		//先頭に追加の場合
		if (task->mPriority >= c->mPriority) {
			//先頭は引数のタスク
			mpHead = task;
			//先頭の前はなし
			task->mpPrev = 0;
			//先頭の次は、カレントc
			task->mpNext = c;
			//次の前は引数のタスク
			c->mpPrev = task;
			return;
		} //先頭に追加の終わり
		c = c->mpNext;
		//先頭以降に追加
		while (c) {
			if (task->mPriority >= c->mPriority) {
				//カレントの前の次を引数のタスクにする
				c->mpPrev->mpNext = task;
				//引数のタスクの前をカレントの前に
				task->mpPrev = c->mpPrev;
				//引数のタスクの次をカレントに
				task->mpNext = c;
				//カレントの前を引数のタスクに
				c->mpPrev = task;
				return;
			}
			c = c->mpNext;
		} //途中に追加終了
		//最後に追加
		//最後の次を引数のタスクにする
		mpTail->mpNext = task;
		//引数のタスクの前を、今の最後にする
		task->mpPrev = mpTail;
		//引数のタスクの次を0にする
		task->mpNext = 0;
		//最後に引数のタスクを代入する
		mpTail = task;
	}
	else {	//0は偽
		//1件目の処理
		//先頭を引数のタスクにする
		mpHead = task;
		//先頭の前を0にする
		task->mpPrev = 0;
		//先頭の次を0にする
		task->mpNext = 0;
		//最後に引数のタスクを代入する
		mpTail = task;
	}
}

/*
Update
更新処理
*/
void CTaskManager::Update(){
	//カレントcを先頭にする
	CXCharacter *c = (CXCharacter*)mpHead;
	//カレントcが0になったら終了
	while (c) {
		//更新する
		c->Update();
		//カレントを次へ
		c = (CXCharacter*)c->mpNext;
	}
}

/*
Render
更新処理
*/
void CTaskManager::Render(){
	//カレントcを先頭にする
	CXCharacter *c = (CXCharacter*)mpHead;
	//カレントcが0になったら終了
	while (c) {
		//描画する
		c->Render();
		//カレントを次へ
		c = (CXCharacter*)c->mpNext;
	}
}

/*
Destory
リストを全て削除し、
自身も削除する
*/
void CTaskManager::Destroy(){
	//カレントcを先頭にする
	CTask *c = mpHead;
	//カレントが0になったら終了
	while (c) {
		//カレントを次にする
		c = c->mpNext;
		//先頭を削除
		delete mpHead;
		//先頭にカレントを代入する
		mpHead = c;
	}
	//最後を0にする
	mpTail = 0;
	//自分自身を削除
	if (sInstance)
		delete sInstance;
	sInstance = 0;
}
/*
引数のタスクをリストから削除します
*/
CTask* CTaskManager::Remove(CTask *task) {
	//削除する次のタスクを退避
	CTask *rtn = task->mpNext;
	//削除リストが先頭の時
	if (mpHead == task) {
		//次を先頭にする
		mpHead = task->mpNext;
	}
	//削除リストが最後の時
	if (mpTail == task) {
		//前を最後にする
		mpTail = task->mpPrev;
	}
	//削除リストに前がある時
	if (task->mpPrev) {
		//前の次を、削除リストの次にする
		task->mpPrev->mpNext = task->mpNext;
	}
	//削除リストに次がある場合
	if (task->mpNext) {
		//次の前を、削除リストの前にする
		task->mpNext->mpPrev = task->mpPrev;
	}
	//タスクの削除
	delete task;
	//次を返す
	return rtn;
}
/*
無効なタスクを削除します
*/
void CTaskManager::Remove() {
	//カレントcを先頭にする
	CTask *c = (CTask*)mpHead;
	//カレントcが0になったら終了
	while (c) {
		if (c->mEnabled) {
			//有効な時は次へ
			c = c->mpNext;
		}
		else {
			//無効なタスクは削除
			c = Remove(c);
		}
	}
}
/*
引数のタスクをリストから削除します
*/
CTask* CCollisionManager::Remove(CTask *task) {
	//削除する次のタスクを退避
	CTask *rtn = task->mpNext;
	//削除リストが先頭の時
	if (mpHead == task) {
		//次を先頭にする
		mpHead = task->mpNext;
	}
	//削除リストが最後の時
	if (mpTail == task) {
		//前を最後にする
		mpTail = task->mpPrev;
	}
	//削除リストに前がある時
	if (task->mpPrev) {
		//前の次を、削除リストの次にする
		task->mpPrev->mpNext = task->mpNext;
	}
	//削除リストに次がある場合
	if (task->mpNext) {
		//次の前を、削除リストの前にする
		task->mpNext->mpPrev = task->mpPrev;
	}
	//タスクの削除
	delete task;
	//次を返す
	return rtn;
}

CTask* CCollisionList::Remove(CTask *task) {
	//削除する次のタスクを退避
	CTask *rtn = task->mpNext;
	//削除リストが先頭の時
	if (mpHead == task) {
		//次を先頭にする
		mpHead = task->mpNext;
	}
	//削除リストが最後の時
	if (mpTail == task) {
		//前を最後にする
		mpTail = task->mpPrev;
	}
	//削除リストに前がある時
	if (task->mpPrev) {
		//前の次を、削除リストの次にする
		task->mpPrev->mpNext = task->mpNext;
	}
	//削除リストに次がある場合
	if (task->mpNext) {
		//次の前を、削除リストの前にする
		task->mpNext->mpPrev = task->mpPrev;
	}
	//タスクの削除
	delete task;
	//次を返す
	return rtn;
}
/*
無効なタスクを削除します
*/
void CCollisionManager::Remove() {
	//mCollisionList[0].Remove();
	//mCollisionList[1].Remove();
	//mCollisionList[2].Remove();
	//mCollisionList[3].Remove();
	//カレントcを先頭にする
	CCollider *c = (CCollider*)mpHead;
	//カレントcが0になったら終了
	while (c && c->mPriority >= CCollider::ENONE) {
		//親が有る
		if (c->mpParent) {
			if (!c->mpParent->mEnabled) {
				//無効なタスクは削除
				c = (CCollider*)Remove(c);
				//ループの先頭へ
				continue;
			}
		}
		//次へ
		c = (CCollider*)c->mpNext;
	}
}

void CCollisionList::Remove() {
	//カレントcを先頭にする
	CCollider *c = (CCollider*)mpHead;
	//カレントcが0になったら終了
	while (c) {
		//親が有る
		if (c->mpParent) {
			if (!c->mpParent->mEnabled) {
				//無効なタスクは削除
				c = (CCollider*)Remove(c);
				//ループの先頭へ
				continue;
			}
		}
		//次へ
		c = (CCollider*)c->mpNext;
	}
}
