#include"CCharacter.h"
//タスクマネージャクラスのインクルード
#include"CTaskManager.h"

CCharacter::CCharacter() {
	//タスクリストに追加
	CTaskManager::Get()->Add(this);
}

void CCharacter::Model(CModel* m)
{
	mpModel = m;
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