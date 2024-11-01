#include "CCharacter3.h"
#include "CApplication.h"

#define GRAVITY -0.1f

CCharacter3::CCharacter3()
	:mpModel(nullptr)
	, mTag(ETag::EZERO)
	, mState(EState::EZERO)
	, mGravity(GRAVITY)
	, mVelocityG(0.0f)
	, mVelocity(0.0f)
	, mGrounded(false)
{
	//タスクリストに追加
//	CApplication::TaskManager()->Add(this);
	CTaskManager::Instance()->Add(this);
}

CCharacter3::CCharacter3(int priority, ETag tag)
	:mpModel(nullptr), mTag(tag)
{
	mPriority = priority;
	CTaskManager::Instance()->Add(this);
}

CCharacter3::CCharacter3(ETag tag)
	: CCharacter3()
{
	mTag = tag;
}

CCharacter3::~CCharacter3()
{
	//タスクリストから削除
//	CApplication::TaskManager()->Remove(this);
	CTaskManager::Instance()->Remove(this);
}

void CCharacter3::Model(CModel* m)
{
	mpModel = m;
}

//描画処理
void CCharacter3::Render()
{
	mpModel->Render(mMatrix);
}
