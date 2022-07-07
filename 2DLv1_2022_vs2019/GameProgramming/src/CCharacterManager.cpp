#include "CCharacterManager.h"

//CCharacterManager* CCharacterManager::Get()
//{
//	//static�ϐ��̍쐬
//	//static�͍ŏ������x�����쐬����폜�͂���Ȃ�
//	static CCharacterManager cm;
//	//CCharacterManager�̃C���X�^���Xcm�̃|�C���^��Ԃ�
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
	//�C�e���[�^�̐���
	std::vector<CCharacter*>::iterator itr;
	//�C�e���[�^��擪��
	itr = mpCharacters.begin();
	//�Ō�܂ŌJ��Ԃ�
	while (itr != mpCharacters.end())
	{
		//�C���X�^���X���폜
		delete* itr;
		//�z�񂩂�폜
		itr = mpCharacters.erase(itr);
	}
}

void CCharacterManager::Delete()
{
	//�C�e���[�^�̐���
	std::vector<CCharacter*>::iterator itr;
	//�C�e���[�^��擪��
	itr = mpCharacters.begin();
	//�Ō�܂ŌJ��Ԃ�
	while (itr != mpCharacters.end())
	{
		if ((*itr)->Enabled())
		{
			//����
			itr++;
		}
		else
		{
			//false�̎��A�C���X�^���X���폜
			delete *itr;
			//�z�񂩂�폜
			itr = mpCharacters.erase(itr);
		}
	}
}
