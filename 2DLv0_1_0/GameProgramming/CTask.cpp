#include <stdio.h>
#include "CTask.h"



void CTask::Enable() {
	switch (mStatus) {
	case EREMOVED:
		mStatus = EENABLED;
		CTaskManager::Get()->Add(this);
		break;
	case EDISABLED:
		mStatus = EENABLED;
		break;
	}
}

void CTask::Auto() {
	switch (mStatus) {
	case EREMOVED:
		mStatus = EAUTO;
		CTaskManager::Get()->Add(this);
		break;
	case EDISABLED:
		mStatus = EAUTO;
		break;
	}
}

void CTask::Disable() {
	mStatus = EDISABLED;
}

void CTask::Delete() {
	mStatus = EDELETE;
}

CTask::~CTask() {
	CTaskManager::Get()->Remove(this);
}



//シングルトン　唯一のインスタンス
CTaskManager *CTaskManager::mInstance = 0;

CTaskManager* CTaskManager::Get() {
	if (!mInstance) {
		//インスタンスが無い場合は生成
		mInstance = new CTaskManager();
	}
	return mInstance;
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
	CTask *c = mpHead;
	//カレントcが0になったら終了
	while (c) {
		//更新する
//		if (c->mStatus == CTask::EENABLED)
			c->Update();
		//カレントを次へ
		c = c->mpNext;
	}
}

/*
Collision
衝突処理
*/
void CTaskManager::Collision(){
	//カレントcを先頭にする
	CTask *c = mpHead;
	//カレントcが0になったら終了
	while (c) {
//		if (c->mStatus == CTask::EENABLED) {
			//衝突処理
			CTask *collider = c->mpNext;
			//カレントcolliderが0になったら終了
			while (collider) {
//				if (collider->mStatus != CTask::EDISABLED) {
					if (c != collider) {
						//衝突処理
						c->Collision(*collider);
						collider->Collision(*c);
					}
//				}
				//カレントを次へ
				collider = collider->mpNext;
			}
//		}
		//カレントを次へ
		c = c->mpNext;
	}
}

/*
Render
更新処理
*/
void CTaskManager::Render(){
	//カレントcを最後にする
	CTask *c = mpTail;
	//カレントcが0になったら終了
	while (c) {
		//描画する
//		if (c->mStatus == CTask::EENABLED)
			c->Render();
		//カレントを前へ
		c = c->mpPrev;
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
		if (mpHead->mStatus != CTask::EAUTO)
			delete mpHead;
		//先頭にカレントを代入する
		mpHead = c;
	}
	//最後を0にする
	mpTail = 0;
	//自分自身を削除
	if (mInstance)
		delete mInstance;
	mInstance = 0;
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
	if (task->mStatus == CTask::EDELETE) {
		task->mStatus = CTask::EREMOVED;
		delete task;
	}
	else {
		task->mpNext = 0;
		task->mpPrev = 0;
		task->mStatus = CTask::EREMOVED;
	}
	//次を返す
	return rtn;
}
/*
無効なタスクをリストから削除します
*/
void CTaskManager::Remove() {
	//カレントcを先頭にする
	CTask *c = (CTask*)mpHead;
	//カレントcが0になったら終了
	while (c) {
		if (c->mStatus == CTask::EENABLED
			|| c->mStatus == CTask::EAUTO) {
				//有効な時は次へ
			c = c->mpNext;
		}
		//else if(c->mStatus == CTask::EDELETE) {
		//	CTask *next = c->mpNext;
		//	delete c;
		//	c = next;
		//}
		else {
			//無効なタスクは削除
			c = Remove(c);
		}
	}
}

////シングルトン　唯一のインスタンス
//CCollisionManager *CCollisionManager::mInstance = 0;
//
//CCollisionManager* CCollisionManager::Get() {
//	if (!mInstance) {
//		//インスタンスが無い場合は生成
//		mInstance = new CCollisionManager();
//	}
//	return mInstance;
//}
///*
//Update
//更新処理
//*/
//void CCollisionManager::Update(CTask& character){
//	//カレントcolliderを先頭にする
//	CTask *collider = mpHead;
//	//カレントcolliderが0になったら終了
//	while (collider) {
//		//更新する
//		character.Collision(*collider);
//		//カレントを次へ
//		collider = collider->mpNext;
//	}
//}
/*
Add
リストに追加する
優先度は大きい値が先
*//*
void CCollisionManager::Add(CTask *task) {
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
引数のタスクをリストから削除します

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
	//	delete task;
	//次を返す
	return rtn;
}
/*
Destory
リストを全て削除し、
自身も削除する

void CCollisionManager::Destroy(){
	//カレントcを先頭にする
	CTask *c = mpHead;
	//カレントが0になったら終了
	while (c) {
		//カレントを次にする
		c = c->mpNext;
		//先頭を削除
		//		delete mpHead;
		//先頭にカレントを代入する
		mpHead = c;
	}
	//最後を0にする
	mpTail = 0;
	//自分自身を削除
	if (mInstance)
		delete mInstance;
	mInstance = 0;
}
*/