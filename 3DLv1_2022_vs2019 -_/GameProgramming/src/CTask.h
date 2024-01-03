#ifndef CTASK_H
#define CTASK_H
class CTaskManager;
/*
タスククラス
タスクリストの要素
*/
class CCollisionManager;
class CColliderManager;
class CColliderList;
class CColliderTask;

class CTask {
	friend CColliderTask;
	friend CCollisionManager;
//	friend CColliderManager;
	friend CColliderList;
	friend CTaskManager;
public:
	//衝突処理
	virtual void Collision(){}
	//デフォルトコンストラクタ
	CTask()
		:mpNext(nullptr),mpPrev(nullptr),mPriority(0),mEnabled(true)
	{}
	//デストラクタ　virtuallにしないと子クラスのデストラクタが呼ばれない
	virtual ~CTask(){}
	//更新
	virtual void Update() {}
	//描画
	virtual void Render() {}
protected:
	int mPriority; //優先度
	bool mEnabled; //有効フラグ
private:
	CTask* mpNext; //次のポイント
	CTask* mpPrev; //前のポインタ
};

#endif
