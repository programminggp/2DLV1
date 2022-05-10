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
