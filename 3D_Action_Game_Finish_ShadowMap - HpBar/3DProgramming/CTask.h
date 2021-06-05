#ifndef CTASK_H
#define CTASK_H

#include "CVector3.h"

class CCollider;
#define COLROW 24	//行列数
#define COLSIZE 12	//一辺の大きさ
/*
タスクの基底クラス
*/
class CTask {
public:
	static bool mShadowMap; //シャドウマップ　true:マップ作成中
	enum EPRI {
		ENONE,
		ELOW,
		EMID,
		EHIGH,
	};
	CTask *mpPrev;	//前
	CTask *mpNext;	//次
	bool mEnabled;	//true:有効
	int mPriority;	//優先度 大：高い

	CTask()
		: mpPrev(0), mpNext(0), mEnabled(true), mPriority(ENONE) {
	}
	virtual ~CTask() {}
	virtual void Render(){}
	virtual void Update(){}
};

class CCollisionList {
	int mCount;
public:
	CTask *mpHead;
	CTask *mpTail;
	CCollisionList()
		: mpHead(0), mpTail(0), mCount(0) {}
	//タスク追加
	void Add(CCollider*);
	//27 更新処理
	void Update(CCollider *c);
	//35 全てを削除
	void Destroy();
	//削除処理
	CTask* Remove(CTask*);
	//削除処理
	void Remove();
};

/*
コリジョンマネージャ
*/
class CCollisionManager {
	enum EAREA {
		EXPZP,
		EXPZM,
		EXMZP,
		EXMZM,
		EMOVE,
	};
	//シングルトン　唯一のインスタンス
	static CCollisionManager *sInstance;
	CTask *mpHead;	//先頭
	CTask *mpTail;	//最後
	CCollisionManager()
		: mpHead(0), mpTail(0), mCount(0) {
	}
//	CCollisionList mCollisionList[EMOVE + 1];
	CCollisionList mCollisionList[COLROW * COLROW];
	int mCount;
public:
	//インスタンスの取得
	static CCollisionManager* Get();
	//タスク追加
	void Add(CTask*);
	//27 更新処理
	void Update();
	//35 全てを削除
	void Destroy();
	//削除処理
	CTask* Remove(CTask*);
	//削除処理
	void Remove();

	int GetIndex(const CVector3& v) {
		int col = ((int)(v.x)) / COLSIZE + COLROW / 2;
		int row = ((int)(v.z)) / COLSIZE + COLROW / 2;
		return row * COLROW + col;
	}

};


/*
タスクマネージャ
*/
class CTaskManager {
	//シングルトン　唯一のインスタンス
	static CTaskManager *sInstance;
	CTask *mpHead;	//先頭
	CTask *mpTail;	//最後
	CTaskManager()
		: mpHead(0), mpTail(0) {
	}
public:
	//インスタンスの取得
	static CTaskManager* Get();
	//タスク追加
	void Add(CTask*);
	//更新処理
	void Update();
	//全てを削除
	void Destroy();
	//描画処理
	void Render();
	//削除処理
	CTask* Remove(CTask*);
	//削除処理
	void Remove();
};


#endif
