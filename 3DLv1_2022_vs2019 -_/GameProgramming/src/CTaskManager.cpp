#include "CTaskManager.h"
//�f�t�H���g�R���X�g���N�^
CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

CTaskManager::~CTaskManager() {
}
//���X�g�ǉ�
//Add(�^�X�N�̃|�C���^)
void CTaskManager::Add(CTask* addTask)
{
	//mHead�̎����猟��
	CTask* task = mHead.mpNext;
	
	//�D��x�̑傫�����ɑ}������
	// �}���ʒu�̌����i�D��x���������傫���Ȃ����O�j
	// mPriority>=0�̂���
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
	//�擪����ƌ�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		task->Update();
		//����
		task = task->mpNext;
	}
}
//�`��
void CTaskManager::Render() {
	//�擪�����Ō�܂ŌJ��Ԃ�
	CTask* task = mTail.mpPrev;
	while (task->mpPrev) {
		task->Render();
		//����
		task = task->mpPrev;
	}
}

void CTaskManager::Remove(CTask* task) {
	//�^�X�N�̑O�̎����A�^�X�N�̎��ɂ���
	task->mpPrev->mpNext = task->mpNext;
	//�^�X�N�̎��̑O���A�^�X�N�̑O�ɂ���
	task->mpNext->mpPrev = task->mpPrev;
}

//�^�X�N�}�l�[�W���̃C���X�^���X
CTaskManager* CTaskManager::mpInstance = nullptr;

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
}

//�C���X�^���X�̎擾
CTaskManager* CTaskManager::Instance()
{
	//�C���X�^���X���Ȃ����
	if (mpInstance == nullptr)
	{
		//�C���X�^���X�𐶐�����
		mpInstance = new CTaskManager();
	}
	return mpInstance;
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

