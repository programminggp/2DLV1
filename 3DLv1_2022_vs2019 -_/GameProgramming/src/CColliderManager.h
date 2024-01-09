#pragma once

#include "CCollider.h"

//�R���C�_�^�X�N�N���X
class CColliderTask : public CTask
{
public:
	//�R���X�g���N�^�i�R���C�_�̃|�C���^�j
	CColliderTask(CCollider* col);
	//�R���C�_�̃|�C���^���擾
	CCollider* Collider();
	~CColliderTask();
private:
	//�R���C�_�ւ̃|�C���^
	CCollider* mpCollider;
};

//�R���C�_���X�g�N���X
class CColliderList {
public:
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask* task);
	//�Փˏ���
	void Collision(CCollider* task);
	//�f�t�H���g�R���X�g���N�^
	CColliderList();
private:
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N
};

#define TASK_LINE 20	//���X�g��TASK_LINE��3�����ɕ��U����
#define MAP_SIZE 100	//�}�b�v�̂����悻�̑傫��

class CColliderManager
{
public:
	//�C���X�^���X�̎擾
	static CColliderManager* Instance();

	//�R���C�_�̒ǉ�
	void Add(CCollider* col);
	//�R���C�_�̏Փˏ���
	void Collision(CCollider* col);

	//�R���C�_�^�X�N�̍폜
	void Remove(CCollider* col);

private:
	//�G���A���̃R���C�_���X�g
	CColliderList mTM[TASK_LINE][TASK_LINE][TASK_LINE];
	//�}�l�[�W���̃C���X�^���X
	static CColliderManager* mpInstance;
};
