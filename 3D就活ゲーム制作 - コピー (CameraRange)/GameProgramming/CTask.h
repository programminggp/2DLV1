#ifndef CTASK_H
#define CTASK_H

class CTaskManager;
class CCollisionManager;
/*
タスククラス
タスクリストの要素
*/
class CTask {
private:
	CTask *mpNext;	//次のポインタ
	CTask *mpPrev;	//前のポインタ
	int mPriority;	//優先度
	bool mEnabled;	//有効フラグ
public:
	void SetPriority(int priority){
		mPriority = priority;
	}
	int GetPriority(){
		return mPriority;
	}
	void SetEnabled(bool enabled){
		mEnabled = enabled;
	}
	bool GetEnabled(){
		return mEnabled;
	}
	//フレンドクラスのクラスではprivate使用可能
	friend CTaskManager;
	friend CCollisionManager;

	//デフォルトコンストラクタ
	CTask()
		: mpNext(0), mpPrev(0), mPriority(0), mEnabled(true) {}
	//デストラクタ
	virtual ~CTask() {}
	//更新
	virtual void Update() {}
	//描画
	virtual void Render() {}

	virtual void TaskCollision() {}
};

#endif
