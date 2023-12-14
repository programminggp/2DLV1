#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"
#include "CCollider.h"

#define COLLISIONRANGE 30 //�Փˏ����͈͂�藣��Ă���R���C�_�͏Փˏ������Ȃ�

class CCollisionManager : public CTaskManager
{
public:
	//�C���X�^���X�̎擾
	static CCollisionManager* Get();
	//�Փˏ���
	void Collision();
	void Collision(CCollider *collider, int range);
private:
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};

#define TASK_LINE 10

class CCollisionManager2
{
public:
	//�C���X�^���X�̎擾
	static CCollisionManager2* Instance();
	//�Փˏ���
//	void Collision();
//	void Collision(CCollider* collider, int range);
	CTaskManager2* TM(const CCollider* col);
private:
	CTaskManager2 mTM[TASK_LINE];
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager2* mpInstance;
};

#endif
