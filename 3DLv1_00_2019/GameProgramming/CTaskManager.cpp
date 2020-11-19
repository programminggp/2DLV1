#include "CTaskManager.h"

//タスクマネージャの外部変数
CTaskManager TaskManager;

CTaskManager::CTaskManager()
//: mpHead(0)//, mpTail(0)
{
//	mpHead = new CTask();
}

CTaskManager::~CTaskManager() {
//	delete mpHead;
}

//リストに追加
//Add(タスクのポインタ)
void CTaskManager::Add(CTask *task) {
	CTask *current = mHead.mpNext;
	//CTask *prev = &mHead;
	//while (current) {
	//	if (task->mPriority >= current->mPriority) {
	//		break;
	//	}
	//	prev = current;
	//	current = current->mpNext;
	//}
	if (current) {
		//currentの前に追加
		//taskの次をcurrent
		task->mpNext = current;
		//taskの前をcurrentの前に
		task->mpPrev = current->mpPrev;
		//taskの前の次をtaskに
		task->mpPrev->mpNext = task;
		//currentの前をtaskに
		current->mpPrev = task;
	}
	else {
		//先頭に追加
		//先頭の次をtaskに
		mHead.mpNext = task;
		//taskの前を先頭に
		task->mpPrev = &mHead;
	}
	return;
	//リストが空（先頭が0）
	//if (mpHead == 0) {
	//	//リストの先頭にする
	//	mpHead = task;
	//	task->mpPrev = 0;
	//	//リストの最後にする
	//	//mpTail = task;
	//	task->mpNext = 0;
	//}
	//else {
		//リストの最後から前に探索
		//CTask *pos = mpTail;
		//while (pos) {
		//	//優先度が小さければ追加
		//	if (pos->mPriority > task->mPriority) {
		//		//posの次がtask
		//		//次を設定
		//		task->mpNext = pos->mpNext;
		//		//前を設定
		//		task->mpPrev = pos;
		//		//前の次を自分に設定
		//		pos->mpNext = task;
		//		//リストの最後なら最終更新
		//		if (task->mpNext == 0) {
		//			mpTail = task;
		//		}
		//		else {
		//			//次の前を自分に設定
		//			task->mpNext->mpPrev = task;
		//		}
		//		return;
		//	}
		//	//前へ
		//	pos = pos->mpPrev;
		//}

		//リストの先頭にする
	//	task->mpNext = mpHead;
	//	mpHead->mpPrev = task;
	//	mpHead = task;
	//	task->mpPrev = 0;
	//}
}

//リストから削除
//Remove(タスクのポインタ)
void CTaskManager::Remove(CTask *task) {
	//taskが先頭の時
	//if (task->mpPrev == 0) {
	//	mpHead = task->mpNext;
	//}
	//else {
		task->mpPrev->mpNext = task->mpNext;
	//}
	//taskが最後の時
	if (task->mpNext == 0) {
//		mpTail = task->mpPrev;
	}
	else {
		task->mpNext->mpPrev = task->mpPrev;
	}
}

//更新
void CTaskManager::Update() {
	//先頭から最後まで繰り返し
	CTask *pos = mHead.mpNext;
	while (pos) {
		//更新処理を呼ぶ
		pos->Update();
		//次へ
		pos = pos->mpNext;
	}
}

//描画
void CTaskManager::Render() {
	//先頭から最後まで繰り返し
	CTask *pos = mHead.mpNext;
	while (pos) {
		//描画処理を呼ぶ
		pos->Render();
		//次へ
		pos = pos->mpNext;
	}
}

//タスクの削除
void CTaskManager::Delete() {
	//先頭から最後まで繰り返し
	CTask *pos = mHead.mpNext;
	while (pos) {
		CTask *del = pos;
		//次へ
		pos = pos->mpNext;
		//mEnabledがfalseなら削除
		if (del->mEnabled == false) {
			delete del;
		}
	}
}
