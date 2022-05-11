#include "CCharacterManager.h"

//CCharacterManager* CCharacterManager::Get()
//{
//	static�ϐ��̍쐬
//	static�͍ŏ��Ɉ�x�쐬����폜����Ȃ�
//	static CCharacterManager cm;
//	CCharacterManager�̃C���X�^���Xcm�̃|�C���^��Ԃ�
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
