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
	: mpModel(nullptr)
	, mTag(EZERO)
	, mState(ESTATEZERO)
{
	//タスクリストに追加
	CTaskManager::Get()->Add(this);
}

