#include "CCharacterManager.h"

CCharacterManager* CCharacterManager::Get()
{
	//static�ϐ��̍쐬
	//static�͍ŏ��Ɉ�x�쐬����폜����Ȃ�
	static CCharacterManager cm;
	//CCharacterManager�̃C���X�^���Xcm�̃|�C���^��Ԃ�
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
