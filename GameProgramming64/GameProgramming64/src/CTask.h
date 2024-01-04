#ifndef CTASK_H
#define CTASK_H

class CTaskManager;
class CColliderList;
class CCollisionManager;
class CColliderTask;

/*
タスククラス
タスクリストの要素
*/
class CTask {
	friend CColliderTask;
	friend CTaskManager;
	friend CColliderList;
	friend CCollisionManager;
public:
	//デフォルトコンストラクタ
	CTask()
		: mpNext(nullptr), mpPrev(nullptr), mPriority(0), mEnabled(true) {}
	//デストラクタ virtualにしないと子クラスのデストラクタが呼ばれない
	virtual ~CTask() {}
	//更新
	virtual void Update() {}
	//描画
	virtual void Render() {}
	//衝突処理
	virtual void TaskCollision() {}
protected:
	int mPriority;	//優先度
	bool mEnabled;	//有効フラグ
private:
	CTask* mpNext;//次のポインタ
	CTask* mpPrev;//前のポインタ
};



#endif
