#include "CTaskManager.h"

CTaskManager::CTaskManager()
: mpHead(0)
, mpTail(0) {}

void CTaskManager::Add(CTask *task) {
	if (mpHead) {
		CTask *c = mpTail;
		while (c != mpHead) {
//		do {
			if (c->mPriority >= task->mPriority) {
				if (c == mpTail) {
					mpTail->mpNext = task;
					task->mpPrev = mpTail;
					//task->mpNext = 0;
					mpTail = task;
					return;
				}
				else {
					task->mpNext = c->mpNext;
					task->mpPrev = c;
					c->mpNext->mpPrev = task;
					c->mpNext = task;
					return;
				}
			}
			c = c->mpPrev;
		}// while (c != mpHead);
		if (c->mPriority < task->mPriority) {
			task->mpNext = mpHead;
//			task->mpPrev = 0;
			mpHead->mpPrev = task;
			mpHead = task;
		}
		else {
			if (c == mpTail) {
				mpTail->mpNext = task;
				task->mpPrev = mpTail;
				//task->mpNext = 0;
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
	//if (mpHead) {
	//	CTask *c = mpHead;
	//	while (c) {
	//		if (task->mPriority >= c->mPriority) {
	//			if (c->mpPrev) {
	//				c->mpPrev->mpNext = task;
	//				task->mpNext = c;
	//				task->mpPrev = c->mpPrev;
	//				c->mpPrev = task;
	//				return;
	//			}
	//			else {
	//				task->mpNext = c;
	//				c->mpPrev = task;
	//				task->mpPrev = 0;
	//				mpHead = task;
	//				return;
	//			}
	//		}
	//		c = c->mpNext;
	//	}
	//	mpTail->mpNext = task;
	//	task->mpPrev = mpTail;
	//	task->mpNext = 0;
	//	mpTail = task;
	//}
	else {
		mpHead = task;
		task->mpPrev = 0;
		task->mpNext = 0;
		mpTail = task;
	}
}

void CTaskManager::Update() {
	CTask *c = mpHead;
	//while (c) {
	//	c->Update();
	//	c = c->mpNext;
	//}
	while(c != mpTail) {
		c->Update();
		c = c->mpNext;
	}
	if (c) {
		c->Update();
	}

}

void CTaskManager::Render() {
	CTask *c = mpHead;
	while (c != mpTail) {
		c->Render();
		c = c->mpNext;
	}
	if (c) {
		c->Render();
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
	if (mpHead == task) {
		mpHead = task->mpNext;
		delete task;
		//if (mpHead) {
		//	mpHead->mpPrev = 0;
		//}
		//else {
		//	mpTail = 0;
		//}
		return;
	}
	if (mpTail == task) {
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
