#include "CCharacterManager.h"

CCharacterManager* CCharacterManager::Get()
{
	//static変数の作成
	//staticは最初に一度作成され削除されない
	static CCharacterManager cm;
	//CCharacterManagerのインスタンスcmのポインタを返す
	return &cm;
}

void CCharacterManager::Add(CCharacter* c)
{
	mCharacters.push_back(c);
}

void CCharacterManager::Update()
{
	for (size_t i = 0; i < mCharacters.size(); i++)
	{
		mCharacters[i]->Update();
	}
}

void CCharacterManager::Render()
{
	for (size_t i = 0; i < mCharacters.size(); i++)
	{
		mCharacters[i]->Render();
	}
}
