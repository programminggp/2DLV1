//�R���C�_�N���X�̃C���N���[�h
#include"CCollider.h"
//�R���W�����}�l�[�W���N���X�̃C���N���[�h
#include "CCollisionManager.h"
//�}�l�[�W���̃C���X�^���X
CCollisionManager* CCollisionManager::mpInstance = nullptr;
//�C���X�^���X�̎擾
CCollisionManager* CCollisionManager::Get()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}
//�Փˏ���
void CCollisionManager::Collision() {
	//���݈ʒu��擪�ɂ���
	CCollider* task = (CCollider*)mHead.mpNext;
	//�Ō�܂ł�����I������
	while (task->mpNext){
		//���݈ʒu�̎������߂�
		CCollider* next = (CCollider*)task->mpNext;
		//�����O�ɂȂ�����I��
		while (next->mpNext){
			//�e�̏Փ˔�����Ăяo��
			//�����̏Փˏ���
			if (task->mpParent)
				task->mpParent->Collision(task, next);
			//����̏Փˏ���
			if (next->mpParent)
				next->mpParent->Collision(next,task);
			//�������߂�
			next = (CCollider*)next->mpNext;

		}
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}

}