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

void CCharacterManager::Collision()
{
	for (size_t i = 0; i < mCharacters.size() - 1; i++)
	{
		for (size_t j = i + 1; j < mCharacters.size(); j++)
		{
			mCharacters[i]->Collision(mCharacters[i], mCharacters[j]);
			mCharacters[j]->Collision(mCharacters[j], mCharacters[i]);
		}
	}
}

void CCharacterManager::Render()
{
	for (size_t i = 0; i < mCharacters.size(); i++)
	{
		mCharacters[i]->Render();
	}
}

void CCharacterManager::Delete()
{
	int i = 0;
	while (i < mCharacters.size())
	{
		if (mCharacters[i]->Enabled())
		{
			i++;
		}
		else
		{
			delete mCharacters[i];
			std::_Erase_remove(mCharacters, mCharacters[i]);
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
