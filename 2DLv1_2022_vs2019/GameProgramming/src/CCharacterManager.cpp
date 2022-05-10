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
	for (size_t i = 0; i < mpCharacters.size() - 1; i++)
	{
		for (size_t j = i + 1; j < mpCharacters.size(); j++)
		{
			mpCharacters[i]->Collision(mpCharacters[i], mpCharacters[j]);
			mpCharacters[j]->Collision(mpCharacters[j], mpCharacters[i]);
		}
	}
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
	int i = 0;
	while (i < mpCharacters.size())
	{
		if (mpCharacters[i]->Enabled())
		{
			i++;
		}
		else
		{
			delete mpCharacters[i];
			std::_Erase_remove(mpCharacters, mpCharacters[i]);
		}
	}
	//イテレータの生成
	//std::vector<CCharacter*>::iterator itr;
	////イテレータを先頭
	//itr = mCharacters.begin();
	////最後まで繰り返し
	//while (itr != mCharacters.end()) {
	//	if ((*itr)->Enabled()) {
	//		//次へ
	//		itr++;
	//	}
	//	else {
	//		//falseのインスタンスを削除
	//		delete* itr;
	//		//リストからも削除
	//		itr = mCharacters.erase(itr);
	//	}
	//}
}
