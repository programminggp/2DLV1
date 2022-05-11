#include "CCharacterManager.h"

//CCharacterManager* CCharacterManager::Get()
//{
//	static変数の作成
//	staticは最初に一度作成され削除されない
//	static CCharacterManager cm;
//	CCharacterManagerのインスタンスcmのポインタを返す
//	return &cm;
//}

void CCharacterManager::Add(CCharacter* c)
{
	mpCharacters.push_back(c);
}

void CCharacterManager::Update()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Update();
	}
}

void CCharacterManager::Collision()
{
}

void CCharacterManager::Render()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Render();
	}
}

void CCharacterManager::Delete()
{
}
