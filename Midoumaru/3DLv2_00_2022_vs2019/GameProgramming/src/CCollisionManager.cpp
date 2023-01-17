#include "CCollisionManager.h"
//
#include "CCollider.h"

//�}�l�[�W���̃C���X�^���X
CCollisionManager* CCollisionManager::mpInstance = 0;
//�C���X�^���X�̎擾
CCollisionManager* CCollisionManager::Get()
{
	if (mpInstance == 0)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}

//�Փˏ���
void CCollisionManager::Collision() {
	//���݈ʒu��擪�ɂ���
	CCollider *task = (CCollider*)mHead.mpNext;
	//�Ō�܂ł�����I������
	while (task->mpNext) {
		//���݈ʒu�̎������߂�
		CCollider *next = (CCollider*)task->mpNext;
		//����0�ɂȂ�����I��
		while (next->mpNext) {
			//�e�̏Փˏ������Ăяo��
			//�����̏Փˏ���
			if (task->mpParent)
				task->mpParent->Collision(task, next);
			//����̏Փˏ���
			if (next->mpParent)
				next->mpParent->Collision(next, task);
			//�������߂�
			next = (CCollider*)next->mpNext;
		}
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
}
//�Փˏ���
//Collision(�R���C�_, �͈�)
//�R���C�_�̗D��x+�͈́`�D��x-�͈͂܂ł̃R���C�_�ƏՓ˔�������s����
void CCollisionManager::Collision(CCollider *c, int range) {
	//���݈ʒu��擪�ɂ���
	CCollider *task = (CCollider*)mHead.mpNext;
	//�͈͂܂œǂݔ�΂�
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority + range)
		{
			break;
		}
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
	//�Ō�܂ł�����I������
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority - range)
		{
			break;
		}
		//�e�̏Փˏ������Ăяo��
		//�����̏Փˏ���
		if (c->mpParent && c != task)
			c->mpParent->Collision(c, task);
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
}
