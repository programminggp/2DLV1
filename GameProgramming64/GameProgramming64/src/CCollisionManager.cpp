#include "CCollisionManager.h"
//
#include "CCollider.h"
#include "CColliderTriangle.h"
#include "CColliderLine.h"

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
	CCollider*task = (CCollider*)mHead.mpNext;
	//�Ō�܂ł�����I������
	while (task->mpNext) {
		//���݈ʒu�̎������߂�
		CCollider*next = (CCollider*)task->mpNext;
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
//	return &mTM[col->mPriority % TASK_LINE];
	int x = (int)(col->mCenter.X()) % 100 / (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z()) % 100 / (100 / TASK_LINE);
	return &mTM[x][z];
}

void CCollisionManager2::Add(CCollider* col)
{
	int x = (int)(col->mCenter.X()) % 100 / (100 / TASK_LINE);
	int z = (int)(col->mCenter.Z()) % 100 / (100 / TASK_LINE);
	int sx = x - 1;
	int ex = x + 1;
	int sz = z - 1;
	int ez = z + 1;
	if (sx < 0) sx = 0;
	if (ex >= TASK_LINE) ex = TASK_LINE - 1;
	if (sz < 0) sz = 0;
	if (ez >= TASK_LINE) ez = TASK_LINE - 1;
	int i = 0;
	for (x = sx; x <= ex; ++x)
	{
		for (z = sz; z <= ez; ++z)
		{
			col->mpColliderTask[i] = new CColliderTask(col);
			mTM[x][z].Add((CTask*)col->mpColliderTask[i++]);
			//switch (col->Type())
			//{
			//case CCollider::EType::ESPHERE:
			//	col->mpSubCollider[i] = new CCollider(false);
			//	*(col->mpSubCollider[i]) = *(CCollider*)col;
			//	mTM[x][z].Add((CTask*)col->mpSubCollider[i++]);
			//	break;
			//case CCollider::EType::ELINE:
			//	col->mpSubCollider[i] = new CColliderLine(false);
			//	*(col->mpSubCollider[i]) = *(CColliderLine*)col;
			//	mTM[x][z].Add((CTask*)col->mpSubCollider[i++]);
			//	break;
			//case CCollider::EType::ETRIANGLE:
			//	col->mpSubCollider[i] = new CColliderTriangle(false);
			//	*(col->mpSubCollider[i]) = *(CColliderTriangle*)col;
			//	mTM[x][z].Add((CTask*)col->mpSubCollider[i++]);
			//	break;
			//}
		}
	}
	//mTM[x][z].Add((CTask*)col);
}

void CCollisionManager2::Remove(CColliderTask* col)
{
	//�^�X�N�̑O�̎����A�^�X�N�̎��ɂ���
	col->mpPrev->mpNext = col->mpNext;
	//�^�X�N�̎��̑O���A�^�X�N�̑O�ɂ���
	col->mpNext->mpPrev = col->mpPrev;
	return;
	int x = (int)(col->Collider()->mCenter.X()) % 100 / (100 / TASK_LINE);
	int z = (int)(col->Collider()->mCenter.Z()) % 100 / (100 / TASK_LINE);
	int sx = x - 1;
	int ex = x + 1;
	int sz = z - 1;
	int ez = z + 1;
	if (sx < 0) sx = 0;
	if (ex >= TASK_LINE) ex = TASK_LINE - 1;
	if (sz < 0) sz = 0;
	if (ez >= TASK_LINE) ez = TASK_LINE - 1;
	int i = 0;
	for (x = sx; x <= ex; ++x)
	{
		for (z = sz; z <= ez; ++z)
		{
			if (col != nullptr)
			{
				mTM[x][z].Remove((CTask*)col);
			}
		}
	}
	//mTM[x][z].Remove((CTask*)col);
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
