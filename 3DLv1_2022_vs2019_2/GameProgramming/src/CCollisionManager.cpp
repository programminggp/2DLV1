#include "CCollisionManager.h"
//�}�l�[�W���̃C���X�^���X
CCollisionManager* CCollisionManager::mpInstance = nullptr;
//�C���X�^���X�̎擾
CCollisionManager* CCollisionManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}
