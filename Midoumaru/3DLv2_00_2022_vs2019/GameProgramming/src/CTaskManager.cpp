#include "CTaskManager.h"

//�^�X�N�}�l�[�W���̊O���ϐ�
//CTaskManager TaskManager;

//�^�X�N�}�l�[�W���̃C���X�^���X
CTaskManager* CTaskManager::mpInstance = 0;
//�C���X�^���X�̎擾
CTaskManager* CTaskManager::Get()
{
	//�C���X�^���X���������
	if (mpInstance == 0)
	{	//�C���X�^���X�𐶐�����
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}

CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

CTaskManager::~CTaskManager() 
{}

//���X�g�ɒǉ�
//Add(�^�X�N�̃|�C���^)
void CTaskManager::Add(CTask *addTask)
{
	//mHead�̎����猟��
	CTask *task = mHead.mpNext;

	//�D��x�̑傫�����ɑ}������
	//�}���ʒu�̌����i�D��x���������傫���Ȃ����O�j
	//mPriority>=0�̂���
	while(addTask->mPriority < task->mPriority)
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
	CTask *task = mHead.mpNext;
	while (task->mpNext) {
		//�X�V�������Ă�
		task->Update();
		//����
		task = task->mpNext;
	}
}
//�`��
void CTaskManager::Render() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask *task = mHead.mpNext;
	while (task->mpNext) {
		//�`�揈�����Ă�
		task->Render();
		//����
		task = task->mpNext;
	}
}
//���X�g����폜
//Remove(�^�X�N�̃|�C���^)
void CTaskManager::Remove(CTask *task) {
	//�^�X�N�̑O�̎����A�^�X�N�̎��ɂ���
	task->mpPrev->mpNext = task->mpNext;
	//�^�X�N�̎��̑O���A�^�X�N�̑O�ɂ���
	task->mpNext->mpPrev = task->mpPrev;
}
//�^�X�N�̍폜
void CTaskManager::Delete() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask *task = mHead.mpNext;
	while (task->mpNext) {
		CTask *del = task;
		//����
		task = task->mpNext;
		//mEnabled��false�Ȃ�폜
		if (del->mEnabled == false) {
			delete del;
		}
	}
}

//�Փˏ���
void CTaskManager::TaskCollision()
{
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask *task = mHead.mpNext;
	while (task->mpNext) {
		//�Փˏ������Ă�
		task->TaskCollision();
		//����
		task = task->mpNext;
	}
}

