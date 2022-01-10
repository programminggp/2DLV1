#include "CCharacter.h"
#include "CTaskManager.h"

void CCharacter::Model(CModel *m)
{
	mpModel = m;
}

CCharacter::ETag CCharacter::Tag()
{
	return mTag;
}

CCharacter::EState CCharacter::State()
{
	return mState;
}

const CVector& CCharacter::KnockBack()
{
	return mKnockBack;
}

float CCharacter::AttackPower()
{
	return mAttackPower;
}

//描画処理
void CCharacter::Render()
{
	mpModel->Render(mMatrix);
}

CCharacter::~CCharacter() {
	//タスクリストから削除
	CTaskManager::Get()->Remove(this);
}

CCharacter::CCharacter()
	: CCharacter(0)
	//: mpModel(nullptr)
	//, mTag(EZERO)
	//, mState(ESTATEZERO)
{
	//タスクリストに追加
	/*CTaskManager::Get()->Add(this);*/
}

CCharacter::CCharacter(int priority)
	: mpModel(nullptr)
	, mTag(EZERO)
	, mState(ESTATEZERO)
	, mAttackPower(0)
{
	mPriority = priority;
	//タスクリストに追加
	CTaskManager::Get()->Add(this);
}

