#ifndef CTASK_H
#define CTASK_H

class CTask
{
public:

	CTask*mpNext; //次ポインタ
	
	CTask*mpPrev; //前ポインタ

	int mPriority;//優先度

	CTask*mpRNext; //次ポインタ

	CTask*mpRPrev; //前ポインタ

	int mRPriority;//優先度

	bool mEnabled;//優効度


	//デフォルトコンストラクタ
	CTask()
		:mpNext(0), mpPrev(0), mPriority(0), mpRNext(0), mpRPrev(0), mRPriority(0), mEnabled(true) {}
	CTask(CTask *task)
		:mpNext(0), mpPrev(0), mPriority(0), mpRNext(0), mpRPrev(0), mRPriority(0), mEnabled(true) {}
	//デストラクタ　virtualにしないと子クラスのデストラクタが呼ばれない
	virtual~CTask(){}

	virtual void Update(){ }
	
	virtual void Render(){ }

	virtual void Collision(CTask*task){ }

};
#endif

