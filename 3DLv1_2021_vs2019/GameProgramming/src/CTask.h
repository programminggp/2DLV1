#ifndef CTASK_H
#define CTASK_H

class CTaskManager;
class CCollisionManager;

/*
タスククラス
タスクリストの要素
*/
class CTask {
	friend CTaskManager;
	friend CCollisionManager;
private:
	CTask* mpNext;//次のポインタ
	CTask* mpPrev;//前のポインタ
protected:
	int mPriority;	//優先度
	bool mEnabled;	//有効フラグ
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
};

#endif
