#include "CTaskManager.h"

CTaskManager::CTaskManager()
: mpHead(0)
, mpTail(0) {}

void CTaskManager::Add(CTask *task) {
	if (mpHead) {
		CTask *c = mpTail;
		while (c != mpHead) {
			if (c->mPriority >= task->mPriority) {
				break;
			}
			c = c->mpPrev;
		}
		if (c->mPriority < task->mPriority) {
			task->mpNext = mpHead;
			task->mpPrev = 0;
			mpHead->mpPrev = task;
			mpHead = task;
		}
		else {
			if (c == mpTail) {
				mpTail->mpNext = task;
				task->mpPrev = mpTail;
				task->mpNext = 0;
				mpTail = task;
			}
			else {
				task->mpNext = c->mpNext;
				task->mpPrev = c;
				c->mpNext->mpPrev = task;
				c->mpNext = task;
			}
		}
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
			Remove(del);
			delete del;
		}
	}
}

void CTaskManager::Remove(CTask *task) {
	if (mpHead == task) {
		if (mpTail == task) {
			mpHead = mpTail = 0;
		}
		else {
			mpHead = task->mpNext;
			mpHead->mpPrev = 0;
		}
		return;
	}
	if (mpTail == task) {
		mpTail = task->mpPrev;
		mpTail->mpNext = 0;
		return;
	}
	task->mpPrev->mpNext = task->mpNext;
	task->mpNext->mpPrev = task->mpPrev;
}

void CTaskManager::Destory() {
	CTask *c = mpHead;
	CTask *del;
	while (c) {
		del = c;
		c = c->mpNext;
		Remove(del);
		delete del;
	}
}
