#include "CTaskManager.h"

CTaskManager::CTaskManager()
: mpHead(0)
, mpTail(0) {}

void CTaskManager::Add(CTask *task) {
	if (mpTail) {
		mpTail->mpNext = task;
		task->mpPrev = mpTail;
		task->mpNext = 0;
		mpTail = task;
		//CTask *c = mpTail->mpPrev;
		//while (c) {
		//	if (c->mPriority < task->mPriority) {

		//	}
		//	else {

		//	}
		//}
		return;
	}
	if (mpHead) {
		CTask *c = mpHead;
		while (c) {
			if (task->mPriority >= c->mPriority) {
				if (c->mpPrev) {
					c->mpPrev->mpNext = task;
					task->mpNext = c;
					task->mpPrev = c->mpPrev;
					c->mpPrev = task;
					return;
				}
				else {
					task->mpNext = c;
					c->mpPrev = task;
					task->mpPrev = 0;
					mpHead = task;
					return;
				}
			}
			c = c->mpNext;
		}
		mpTail->mpNext = task;
		task->mpPrev = mpTail;
		task->mpNext = 0;
		mpTail = task;
	}
	else {
		mpHead = task;
		task->mpPrev = 0;
		task->mpNext = 0;
		mpTail = task;
	}
}

void CTaskManager::Update() {
	CTask *c = mpHead;
	while (c) {
		c->Update();
		c = c->mpNext;
	}
}

void CTaskManager::Render() {
	CTask *c = mpHead;
	while (c) {
		c->Render();
		c = c->mpNext;
	}
}

void CTaskManager::Delete() {
	CTask *c = mpHead;
	CTask *del;
	while (c) {
		if (c->mEnabled) {
			c = c->mpNext;
		}
		else {
			del = c;
			c = c->mpNext;
			Delete(del);
		}
	}
}

void CTaskManager::Delete(CTask *task) {
	if (task->mpPrev == 0) {
		mpHead = task->mpNext;
		delete task;
		if (mpHead) {
			mpHead->mpPrev = 0;
		}
		else {
			mpTail = 0;
		}
		return;
	}
	if (task->mpNext == 0) {
		mpTail = task->mpPrev;
		mpTail->mpNext = 0;
		delete task;
		return;
	}
	task->mpPrev->mpNext = task->mpNext;
	task->mpNext->mpPrev = task->mpPrev;
	delete task;
}

void CTaskManager::Destory() {
	CTask *c = mpHead;
	CTask *del;
	while (c) {
		del = c;
		c = c->mpNext;
		Delete(del);
	}
}
