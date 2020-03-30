#include"CTaskManager.h"
//タスクマネージャの外部変数
CTaskManager TaskManager;

CTaskManager::CTaskManager()
:mpHead(0), mpRHead(0)
{}

CTaskManager::~CTaskManager(){}


void CTaskManager::Add(CTask *task, int priority, int priorityr) {
	task->mPriority = priority;
	task->mRPriority = priorityr;
	Add(task);
	AddR(task);
}


//タスク追加
void CTaskManager::Add(CTask*task){

	if (mpHead == 0){

		mpHead = task;

		task->mpPrev = 0;

		task->mpNext = 0;
	}
	else{

		CTask*pos = mpHead;

		while (task->mPriority < pos->mPriority){

			if (pos->mpNext != 0){

				pos = pos->mpNext;

			}

			else{

				break;

			}

		}

		if (pos->mpPrev == 0){

			task->mpNext = mpHead;

			mpHead->mpPrev = task;

			mpHead = task;

			mpHead->mpPrev = 0;

		}

		else if (pos->mpNext == 0){

			task->mpNext = 0;

			task->mpPrev = pos;

			pos->mpNext = task;

		}

		else{

			task->mpNext = pos;

			task->mpPrev = pos->mpPrev;

			pos->mpPrev = task;

			task->mpPrev->mpNext = task;

		}

	}
}

void CTaskManager::AddR(CTask*task){

	if (mpRHead == 0){

		mpRHead = task;

		task->mpRPrev = 0;

		task->mpRNext = 0;
	}
	else{

		CTask*pos = mpRHead;

		while (task->mRPriority < pos->mRPriority){

			if (pos->mpRNext != 0){

				pos = pos->mpRNext;

			}

			else{

				break;

			}

		}

		if (pos->mpRPrev == 0){

			task->mpRNext = mpRHead;

			mpRHead->mpRPrev = task;

			mpRHead = task;

			mpRHead->mpRPrev = 0;

		}

		else if (pos->mpRNext == 0){

			task->mpRNext = 0;

			task->mpRPrev = pos;

			pos->mpRNext = task;

		}

		else{

			task->mpRNext = pos;

			task->mpRPrev = pos->mpRPrev;

			pos->mpRPrev = task;

			task->mpRPrev->mpRNext = task;

		}

	}
}

void CTaskManager::AllDisable(){
	CTask*pos = mpHead;

	while (pos)
	{
		//更新処理の呼び出し

		pos->mEnabled=false;

		//次へ行く
		pos = pos->mpNext;
	}

}
void CTaskManager::Changepriority(CTask*task, int priority){

	RemoveR(task);
	task->mRPriority = priority;
	AddR(task);
}

void CTaskManager::Remove(CTask*task){
	//1つのtaskをリストから削除
	if (task->mpPrev == 0){
		mpHead = task->mpNext;
	}
	else{
		task->mpPrev->mpNext = task->mpNext;
	}
	if (task->mpNext != 0){
		task->mpNext->mpPrev = task->mpPrev;
	}

	RemoveR(task);
}

void CTaskManager::RemoveR(CTask*task){
	//1つのtaskをリストから削除
	if (task->mpRPrev == 0){
		mpRHead = task->mpRNext;
	}
	else{
		task->mpRPrev->mpRNext = task->mpRNext;
	}
	if (task->mpRNext != 0){
		task->mpRNext->mpRPrev = task->mpRPrev;
	}
}

////生存確認
//void CTaskManager::DeleteCheck(){
//	//先頭から最後まで繰り返し
//	CTask*pos = mpHead;
//	while (pos){
//		CTask*mpMine = pos;
//		//次へ
//		pos = pos->mpNext;
//		//mSurvivalConfirmation(生存確認)がfalseなら削除
//		if (mpMine->mSurvivalConfirmation == false){
//			delete mpMine;
//		}
//	}
//}

void CTaskManager::Delete(){

	CTask*pos = mpHead;

	while (pos){
		CTask*del = pos;
		//次へ
		pos = pos->mpNext;
		//mEnabledがfalseなら消去

		if (del->mEnabled == false){
			Remove(del);
			delete del;
		}
	}

}


void CTaskManager::Update(){

	CTask*pos = mpHead;

	while (pos)
	{
		//更新処理の呼び出し

		pos->Update();

		//次へ行く
		pos = pos->mpNext;
	}

}

void CTaskManager::Collision(){
	//現在位置を先頭にする
	CTask*pos = (CTask*)mpHead;
	//最後までできたら終了する
	while (pos ->mpNext!=0 ){
		//現在位置の次を求める
		CTask*next = (CTask*)pos->mpNext;
		//次が0になったら終了
		while (next){
			//親の衝突処理を呼び出す
			//自分の衝突処理
			pos->Collision(next);
			//相手の衝突処理
			next->Collision(pos);
			//次を求める
			next = next->mpNext;
		}
		//現在位置をつぎにする
		pos = pos->mpNext;
	}
}

void CTaskManager::Render(){

	CTask*pos = mpRHead;

	while (pos)
	{
		//描画処理の呼び出し

		pos->Render();

		//次へ行く
		pos = pos->mpRNext;
	}

}

//void CTaskManager::AllDelete(){
//
//	CTask*pos = mpHead;
//
//	while (pos){
//		CTask*del = pos;
//		//次へ
//		pos = pos->mpNext;
//		//mEnabledがfalseなら消去
//
//			delete del;
//
//	}
//
//}