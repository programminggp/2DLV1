#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"

class CCollisionManager : public CTaskManager
{
public:
	//�Փˏ���
	void Collision();
	//�C���X�^���X�̎擾
	static CCollisionManager* Instance();
private:
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};

#endif
