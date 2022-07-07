#include "CCharacterManager.h"

//CCharacterManager* CCharacterManager::Get()
//{
//	//static変数の作成
//	//staticは最初から一度だけ作成され削除はされない
//	static CCharacterManager cm;
//	//CCharacterManagerのインスタンスcmのポインタを返す
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
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Collision();
	}
}

void CCharacterManager::Collision(CCharacter* character)
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		character->Collision(character, mpCharacters[i]);
	}
}

void CCharacterManager::Render()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Render();
	}
}

void CCharacterManager::AllDelete()
{
	//イテレータの生成
	std::vector<CCharacter*>::iterator itr;
	//イテレータを先頭へ
	itr = mpCharacters.begin();
	//最後まで繰り返し
	while (itr != mpCharacters.end())
	{
		//インスタンスを削除
		delete* itr;
		//配列から削除
		itr = mpCharacters.erase(itr);
	}
}

void CCharacterManager::Delete()
{
	//イテレータの生成
	std::vector<CCharacter*>::iterator itr;
	//イテレータを先頭へ
	itr = mpCharacters.begin();
	//最後まで繰り返し
	while (itr != mpCharacters.end())
	{
		if ((*itr)->Enabled())
		{
			//次へ
			itr++;
		}
		else
		{
			//falseの時、インスタンスを削除
			delete *itr;
			//配列から削除
			itr = mpCharacters.erase(itr);
		}
	}
}
