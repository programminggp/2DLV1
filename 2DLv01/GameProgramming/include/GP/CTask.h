#ifndef CTASK_H
#define CTASK_H

/*
タスクの基底クラス
*/
class CTask {
	CTask *mpPrev;	//前
	CTask *mpNext;	//次
public:
	enum EStatus {
		EREMOVED,
		EDISABLED,
		EENABLED,
		EDELETE,
	};
	EStatus mStatus;//ステータス
	int mPriority;	//優先度 大：高い

	CTask()
		: mpPrev(0), mpNext(0), mPriority(0), mStatus(EREMOVED) {
	}
	virtual ~CTask();

	virtual void Render(){}
	virtual void Collision(CTask&){}
	virtual void Update(){}
	void Enable();
	void Disable();
	void Delete();

	friend class CTaskManager;
};

/*
タスクマネージャ
*/
class CTaskManager {
	//シングルトン　唯一のインスタンス
	static CTaskManager *mInstance;
protected:
	CTaskManager()
		: mpHead(0), mpTail(0) {
	}
	CTask *mpHead;	//先頭
	CTask *mpTail;	//最後
public:
	//インスタンスの取得
	static CTaskManager* Get();
	//タスク追加
	void Add(CTask*);
	//更新処理
	void Update();
	//衝突処理
	void Collision();
	//全てを削除
	void Destroy();
	//描画処理
	void Render();
	//削除処理
	CTask* Remove(CTask*);
	//削除処理
	void Remove();
};
/*
コリジョンマネージャ
*/
//class CCollisionManager : public CTaskManager {
//	//シングルトン　唯一のインスタンス
//	static CCollisionManager *mInstance;
//	CCollisionManager()
//		: CTaskManager() {
////		: mpHead(0), mpTail(0) {
//	}
////	CTask *mpHead;	//先頭
////	CTask *mpTail;	//最後
//public:
//	//インスタンスの取得
//	static CCollisionManager* Get();
//	//更新処理
//	void Update(CTask&);
//	//タスク追加
////	void Add(CTask*);
//	//全てを削除
////	void Destroy();
//	//削除処理
////	CTask* Remove(CTask*);
//};

#endif
