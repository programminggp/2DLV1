#include "CTask.h"
#include "CTaskManager.h"
#include "CCharacter.h"

//�R���X�g���N�^
CTask::CTask(int priority)
	: mpprev(nullptr)
	, mpnext(nullptr)
	, mpriority(priority)
	, mTag(ETag::EZERO)
{
	CTaskManager::Instance()->Add(this);
}

//�f�X�g���N�^
CTask::~CTask()
{
	CTaskManager::Instance()->Remove(this);
}

//�D��x��ݒ�
void CTask::Setpriority(int priority)
{
	//�D��x��ݒ�
	mpriority = priority;
	//�V�����D��x�̈ʒu�Ƀ^�X�N��z�u
	CTaskManager::Instance()->Remove(this);
	CTaskManager::Instance()->Add(this);
}

//�D��x���擾
int CTask::GetPriority() const
{
	return mpriority;
}

void CTask::Delete()
{
	CTaskManager::Instance()->Delete(this);
}

CTask::ETag CTask::Tag()
{
	return mTag;
}
