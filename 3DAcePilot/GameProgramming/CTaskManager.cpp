#include "CTaskManager.h"

//�^�X�N�}�l�[�W���̊O���ϐ�
CTaskManager TaskManager;

CTaskManager::CTaskManager()
//: mpHead(0)//, mpTail(0)
{
	mpHead = new CTask();
}

CTaskManager::~CTaskManager() {
	delete mpHead;
}

//���X�g�ɒǉ�
//Add(�^�X�N�̃|�C���^)
void CTaskManager::Add(CTask *task) {
	CTask *current = mpHead->mpNext;
	CTask *prev = mpHead;
	while (current) {
		if (task->mPriority >= current->mPriority) {
			break;
		}
		prev = current;
		current = current->mpNext;
	}
	if (current) {
		prev->mpNext = task;
		current->mpPrev = task;
		task->mpPrev = prev;
		task->mpNext = current;
	}
	else {
		prev->mpNext = task;
		task->mpPrev = prev;
		task->mpNext = 0;
	}
	return;
	//���X�g����i�擪��0�j
	if (mpHead == 0) {
		//���X�g�̐擪�ɂ���
		mpHead = task;
		task->mpPrev = 0;
		//���X�g�̍Ō�ɂ���
		//mpTail = task;
		task->mpNext = 0;
	}
	else {
		//���X�g�̍Ōォ��O�ɒT��
		//CTask *pos = mpTail;
		//while (pos) {
		//	//�D��x����������Βǉ�
		//	if (pos->mPriority > task->mPriority) {
		//		//pos�̎���task
		//		//����ݒ�
		//		task->mpNext = pos->mpNext;
		//		//�O��ݒ�
		//		task->mpPrev = pos;
		//		//�O�̎��������ɐݒ�
		//		pos->mpNext = task;
		//		//���X�g�̍Ō�Ȃ�ŏI�X�V
		//		if (task->mpNext == 0) {
		//			mpTail = task;
		//		}
		//		else {
		//			//���̑O�������ɐݒ�
		//			task->mpNext->mpPrev = task;
		//		}
		//		return;
		//	}
		//	//�O��
		//	pos = pos->mpPrev;
		//}

		//���X�g�̐擪�ɂ���
		task->mpNext = mpHead;
		mpHead->mpPrev = task;
		mpHead = task;
		task->mpPrev = 0;
	}
}

//���X�g����폜
//Remove(�^�X�N�̃|�C���^)
void CTaskManager::Remove(CTask *task) {
	//task���擪�̎�
	if (task->mpPrev == 0) {
		mpHead = task->mpNext;
	}
	else {
		task->mpPrev->mpNext = task->mpNext;
	}
	//task���Ō�̎�
	if (task->mpNext == 0) {
//		mpTail = task->mpPrev;
	}
	else {
		task->mpNext->mpPrev = task->mpPrev;
	}
}

//�X�V
void CTaskManager::Update() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask *pos = mpHead->mpNext;
	while (pos) {
		//�X�V�������Ă�
		pos->Update();
		//����
		pos = pos->mpNext;
	}
}

//�`��
void CTaskManager::Render() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask *pos = mpHead->mpNext;
	while (pos) {
		//�`�揈�����Ă�
		pos->Render();
		//����
		pos = pos->mpNext;
	}
}

//�^�X�N�̍폜
void CTaskManager::Delete() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask *pos = mpHead->mpNext;
	while (pos) {
		CTask *del = pos;
		//����
		pos = pos->mpNext;
		//mEnabled��false�Ȃ�폜
		if (del->mEnabled == false) {
			delete del;
		}
	}
}
