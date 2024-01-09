#include "CColliderManager.h"

//�R���C�_�̕ێ�
CColliderTask::CColliderTask(CCollider* col)
	: mpCollider(col)
{
}

//�R���C�_�̃|�C���^��Ԃ�
CCollider* CColliderTask::Collider()
{
	return mpCollider;
}

//���X�g����폜
CColliderTask::~CColliderTask()
{
	//�O�̃^�X�N�̎����A���̃^�X�N�ɂ���
	mpPrev->mpNext = mpNext;
	//���̃^�X�N�̑O���A�O�̃^�X�N�ɂ���
	mpNext->mpPrev = mpPrev;
}


/////////////////////////////////////////////
//CColliderList

CColliderList::CColliderList()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

//���X�g�ɒǉ�
//Add(�^�X�N�̃|�C���^)
void CColliderList::Add(CTask* addTask)
{
	CTask* task = &mTail;
	//addTask�̎���task
	addTask->mpNext = task;
	//addTask�̑O��task�̑O��
	addTask->mpPrev = task->mpPrev;
	//addTask�̑O�̎���addTask��
	addTask->mpPrev->mpNext = addTask;
	//task�̑O��addTask��
	task->mpPrev = addTask;
}

void CColliderList::Collision(CCollider* task)
{
	//���݈ʒu��擪�ɂ���
	CColliderTask* next = (CColliderTask*)mHead.mpNext;
	//�Ō�܂ł�����I������
	//����0�ɂȂ�����I��
	while (next->mpNext) {
		//�e�̏Փˏ������Ăяo��
		//�����̏Փˏ���
		if (task->Parent() != next->Collider()->Parent())
			if (task->Parent() && task != next->Collider())
				task->Parent()->Collision(task, next->Collider());
		//�������߂�
		next = (CColliderTask*)next->mpNext;
	}
}


//�}�l�[�W���̃C���X�^���X
CColliderManager* CColliderManager::mpInstance = nullptr;
//�C���X�^���X�̎擾
CColliderManager* CColliderManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CColliderManager();
	}
	return mpInstance;
}

void CColliderManager::Add(CCollider* col)
{
	//���S���W����G���A�����߂�
	int y = (int)(col->mCenter.Y() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	int x = (int)(col->mCenter.X() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);

	//�אڃG���A�����߂�
	int ys = y - 1;
	int ye = y + 1;
	int xs = x - 1;
	int xe = x + 1;
	int zs = z - 1;
	int ze = z + 1;
	//�Y�����͈͓̔��ɂ����߂�
	if (ys < 0) ys = 0;
	if (ye >= TASK_LINE) ye = TASK_LINE - 1;
	if (xs < 0) xs = 0;
	if (xe >= TASK_LINE) xe = TASK_LINE - 1;
	if (zs < 0) zs = 0;
	if (ze >= TASK_LINE) ze = TASK_LINE - 1;
	//�R���C�_�^�X�N�𐶐������X�g�ɒǉ�����
	int i = 0;
	for (y = ys; y <= ye; ++y)
	{
		for (x = xs; x <= xe; ++x)
		{
			for (z = zs; z <= ze; ++z)
			{
				col->mpColliderTask[i] = new CColliderTask(col);
				mTM[y][x][z].Add(
					(CTask*)col->mpColliderTask[i++]);
			}
		}
	}
}

void CColliderManager::Remove(CCollider* col)
{
	//�R���C�_�ɂ���R���C�_�^�X�N��S�č폜
	for (int i = 0; i < COLLIDERTASK_SIZE; ++i)
	{
		if (col->mpColliderTask[i] != nullptr)
		{
			delete col->mpColliderTask[i];
			col->mpColliderTask[i] = nullptr;
		}
	}
}

void CColliderManager::Collision(CCollider* col)
{
	//���Y�G���A�����߁A�R���C�_���X�g�̏Փˏ������Ă�
	int y = (int)(col->mCenter.Y() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	int x = (int)(col->mCenter.X() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z() * 100 / MAP_SIZE) % 100
		/ (100 / TASK_LINE);
	if (y < 0) y = 0;
	if (y >= TASK_LINE) y = TASK_LINE - 1;
	if (x < 0) x = 0;
	if (x >= TASK_LINE) x = TASK_LINE - 1;
	if (z < 0) z = 0;
	if (z >= TASK_LINE) z = TASK_LINE - 1;
	mTM[y][x][z].Collision(col);
}

