#pragma once

#include "CCollider.h"

#define TASK_LINE 20	//���X�g��TASK_LINE*TASK_LINE�ŕ��U����
#define MAP_SIZE 200

class CTaskManager2 {
public:
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask* task);
	//�Փˏ���
	void Collision(CCollider* task);
	//�f�t�H���g�R���X�g���N�^
	CTaskManager2();
	//
	void Render();
protected:
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N
};

class CCollisionManager2
{
public:
	//�C���X�^���X�̎擾
	static CCollisionManager2* Instance();

	//�^�X�N���X�g�̎擾
	CTaskManager2* TM(const CCollider* col);

	void Add(CCollider* col);
	void Remove(CColliderTask* col);
	void Delete(CCollider* col);

private:
	CTaskManager2 mTM[TASK_LINE][TASK_LINE][TASK_LINE];
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager2* mpInstance;
};
