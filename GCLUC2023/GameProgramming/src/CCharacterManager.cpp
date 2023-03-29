#include "CCharacterManager.h"
#include "CTaskManager.h"
CCharacterManager* CCharacterManager::mpinstance = 0;

//全インスタンスを削除
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

//不要なポインタを削除する
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
			delete* itr;
			//配列から削除
			itr = mpCharacters.erase(itr);
		}
	}
}

//インスタンス作成
CCharacterManager* CCharacterManager::Instance()
{
	if (mpinstance == nullptr)
	{
		mpinstance = new CCharacterManager();
	}
	return mpinstance;
}

//衝突処理1
void CCharacterManager::Collision()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Collision();
	}
}

//衝突処理3
void CCharacterManager::Collision(CCharacter* character)
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		character->Collision(character, mpCharacters[i]);
	}
}

//可変長配列の後ろに追加する
void CCharacterManager::Add(CCharacter* c)
{
	mpCharacters.push_back(c);
}

//可変長配列にあるポインタのUpdate()を実行していく
void CCharacterManager::Update()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Update();
	}
}

//可変長配列にあるポインタのRender()を実行していく
void CCharacterManager::Render()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Render();
	}
}