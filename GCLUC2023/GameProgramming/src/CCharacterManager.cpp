#include "CCharacterManager.h"
#include "CTaskManager.h"
CCharacterManager* CCharacterManager::mpinstance = 0;

//�S�C���X�^���X���폜
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

//�s�v�ȃ|�C���^���폜����
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
			delete* itr;
			//�z�񂩂�폜
			itr = mpCharacters.erase(itr);
		}
	}
}

//�C���X�^���X�쐬
CCharacterManager* CCharacterManager::Instance()
{
	if (mpinstance == nullptr)
	{
		mpinstance = new CCharacterManager();
	}
	return mpinstance;
}

//�Փˏ���1
void CCharacterManager::Collision()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Collision();
	}
}

//�Փˏ���3
void CCharacterManager::Collision(CCharacter* character)
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		character->Collision(character, mpCharacters[i]);
	}
}

//�ϒ��z��̌��ɒǉ�����
void CCharacterManager::Add(CCharacter* c)
{
	mpCharacters.push_back(c);
}

//�ϒ��z��ɂ���|�C���^��Update()�����s���Ă���
void CCharacterManager::Update()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Update();
	}
}

//�ϒ��z��ɂ���|�C���^��Render()�����s���Ă���
void CCharacterManager::Render()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Render();
	}
}