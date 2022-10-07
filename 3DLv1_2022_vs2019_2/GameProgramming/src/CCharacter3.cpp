#include "CCharacter3.h"
#include "CApplication.h"

CCharacter3::CCharacter3()
{
	//タスクリストに追加
//	CApplication::TaskManager()->Add(this);
	CTaskManager::Instance()->Add(this);
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
