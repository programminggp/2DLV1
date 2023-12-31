#pragma once

#include "CCollider.h"

#define TASK_LINE 20	//���X�g��TASK_LINE*TASK_LINE*TASK_LINE�ŕ��U����
#define MAP_SIZE 200	//�}�b�v��1�ӂ̑傫��

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

	//�R���C�_�̒ǉ�
	void Add(CCollider* col);
	//�R���C�_�̍폜
	void Delete(CCollider* col);
	//�R���C�_�̏Փˏ���
	void Collision(CCollider* col);

	//�R���C�_�^�X�N���X�g����폜
	void Remove(CColliderTask* col);
private:
	//�R���C�_�^�X�N���X�g�z��
	CTaskManager2 mTM[TASK_LINE][TASK_LINE][TASK_LINE];
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager2* mpInstance;
};
