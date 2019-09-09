#ifndef CTASKMANAGER
#define CTASKMANAGER

#include "CTask.h"

class CTaskManager {
protected:
	CTask *mpHead;
	CTask *mpTail;
public:
	CTaskManager();
	void Add(CTask *task);
	void Update();
	void Render();
	void Delete();
	void Remove(CTask *task);
	void Destory();
};


#endif
