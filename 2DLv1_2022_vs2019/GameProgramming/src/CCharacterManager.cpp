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
	//�C�e���[�^�̐���
	//std::vector<CCharacter*>::iterator itr;
	////�C�e���[�^��擪
	//itr = mCharacters.begin();
	////�Ō�܂ŌJ��Ԃ�
	//while (itr != mCharacters.end()) {
	//	if ((*itr)->Enabled()) {
	//		//����
	//		itr++;
	//	}
	//	else {
	//		//false�̃C���X�^���X���폜
	//		delete* itr;
	//		//���X�g������폜
	//		itr = mCharacters.erase(itr);
	//	}
	//}
}
