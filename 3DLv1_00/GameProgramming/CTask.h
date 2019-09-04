#ifndef CTASK
#define CTASK

class CTask {
public:
	CTask *mpNext;
	CTask *mpPrev;
	int mPriority;
	bool mEnabled;
	CTask()
		: mpNext(0)
		, mpPrev(0)
		, mPriority(0)
		, mEnabled(true) {}
	virtual ~CTask() {};
	virtual void Update() {};
	virtual void Render() {};
};


#endif
