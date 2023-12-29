#include "CCollisionManager2.h"

/////////////////////////////////////////////
//CTaskManager2

CTaskManager2::CTaskManager2()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

//���X�g�ɒǉ�
//Add(�^�X�N�̃|�C���^)
void CTaskManager2::Add(CTask* addTask)
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

void CTaskManager2::Render()
{
	//���݈ʒu��擪�ɂ���
	CColliderTask* next = (CColliderTask*)mHead.mpNext;
	//�Ō�܂ł�����I������
	//����0�ɂȂ�����I��
	while (next->mpNext) {
		//�e�̏Փˏ������Ăяo��
		//�����̏Փˏ���
		next->Collider()->Render();
		//�������߂�
		next = (CColliderTask*)next->mpNext;
	}
}

void CTaskManager2::Collision(CCollider* task)
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
CCollisionManager2* CCollisionManager2::mpInstance = 0;
//�C���X�^���X�̎擾
CCollisionManager2* CCollisionManager2::Instance()
{
	if (mpInstance == 0)
	{
		mpInstance = new CCollisionManager2();
	}
	return mpInstance;
}

CTaskManager2* CCollisionManager2::TM(const CCollider* col)
{
	int y = (int)(col->mCenter.Y() * 100 / MAP_SIZE) % 100 / (100 / TASK_LINE);
	int x = (int)(col->mCenter.X() * 100 / MAP_SIZE) % 100 / (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z() * 100 / MAP_SIZE) % 100 / (100 / TASK_LINE);
	if (y < 0) y = 0;
	if (y >= TASK_LINE) y = TASK_LINE - 1;
	if (x < 0) x = 0;
	if (x >= TASK_LINE) x = TASK_LINE - 1;
	if (z < 0) z = 0;
	if (z >= TASK_LINE) z = TASK_LINE - 1;
	return &mTM[y][x][z];
}

void CCollisionManager2::Add(CCollider* col)
{
	int y = (int)(col->mCenter.Y() * 100 / MAP_SIZE) % 100 / (100 / TASK_LINE);
	int x = (int)(col->mCenter.X() * 100 / MAP_SIZE) % 100 / (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z() * 100 / MAP_SIZE) % 100 / (100 / TASK_LINE);
	int sy = y - 1;
	int ey = y + 1;
	int sx = x - 1;
	int ex = x + 1;
	int sz = z - 1;
	int ez = z + 1;
	if (sy < 0) sy = 0;
	if (ey >= TASK_LINE) ey = TASK_LINE - 1;
	if (sx < 0) sx = 0;
	if (ex >= TASK_LINE) ex = TASK_LINE - 1;
	if (sz < 0) sz = 0;
	if (ez >= TASK_LINE) ez = TASK_LINE - 1;
	int i = 0;
	for (y = sy; y <= ey; ++y)
	{
		for (x = sx; x <= ex; ++x)
		{
			for (z = sz; z <= ez; ++z)
			{
				col->mpColliderTask[i] = new CColliderTask(col);
				mTM[y][x][z].Add((CTask*)col->mpColliderTask[i++]);
			}
		}
	}
}

void CCollisionManager2::Remove(CColliderTask* col)
{
	//�^�X�N�̑O�̎����A�^�X�N�̎��ɂ���
	col->mpPrev->mpNext = col->mpNext;
	//�^�X�N�̎��̑O���A�^�X�N�̑O�ɂ���
	col->mpNext->mpPrev = col->mpPrev;
	return;
}

void CCollisionManager2::Delete(CCollider* col)
{
	for (int i = 0; i < 9; ++i)
	{
		if (col->mpColliderTask[i] != nullptr)
		{
			delete col->mpColliderTask[i];
			col->mpColliderTask[i] = nullptr;
		}
	}
}
