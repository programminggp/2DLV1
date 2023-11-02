#include "CTaskManager.h"

//�f�t�H���g�R���X�g���N�^
CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

void CTaskManager::Delete() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		CTask* del = task;
		//����
		task = task->mpNext;
		//mEnabled��false�Ȃ�폜
		if (del->mEnabled == false) {
			delete del;
		}
	}
}

void CTaskManager::Remove(CTask* task)
{
	//�^�X�N�̑O�̎����A�^�X�N�̎��ɂ���
	task->mpPrev->mpNext = task->mpNext;
	//�^�X�N�̎��̑O���A�^�X�N�̑O�ɂ���
	task->mpNext->mpPrev = task->mpPrev;
}
CTaskManager::~CTaskManager() {
}
//���X�g�ɒǉ�
//Add(�^�X�N�̃|�C���^)
void CTaskManager::Add(CTask* addTask)
{
	//mHead�̎����猟��
	CTask* task = mHead.mpNext;

	//�D��x�̑傫�����ɑ}������
	//�}���ʒu�̌����i�D��x���������傫���Ȃ����O�j
	//mPriority>=0�̂���
	while (addTask->mPriority < task->mPriority)
	{
		task = task->mpNext; //����
	}

	//addTask�̎���task
	addTask->mpNext = task;
	//addTask�̑O��task�̑O��
	addTask->mpPrev = task->mpPrev;
	//addTask�̑O�̎���addTask��
	addTask->mpPrev->mpNext = addTask;
	//task�̑O��addTask��
	task->mpPrev = addTask;
}

//�X�V
void CTaskManager::Update() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//�X�V�������Ă�
		task->Update();
		//����
		task = task->mpNext;
	}
}

//�`��
void CTaskManager::Render() {
	//�Ōォ��擪�܂ŌJ��Ԃ�
	CTask* task = mTail.mpPrev;
	while (task->mpPrev) {
		//�`�揈�����Ă�
		task->Render();
		//����
		task = task->mpPrev;
	}
}

//�Փˏ���
void CTaskManager::Collision()
{
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//�Փˏ������Ă�
		task->Collision();
		//����
		task = task->mpNext;
	}

	/*
	//���݈ʒu��擪�ɂ���
	CCollider* task = (CCollider*)mHead.mpNext;
	//�Ō�܂ł�����I������
	while (task->mpNext) {
		//���݈ʒu�̎������߂�
		CCollider* next = (CCollider*)task->mpNext;
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
	*/
}

void CTaskManager::Collision(CCollider* c, int range)
{
	//���݈ʒu��擪�ɂ���
	CCollider* task = (CCollider*)mHead.mpNext;
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