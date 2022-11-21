#include "CCharacter3.h"
#include "CApplication.h"

CCharacter3::CCharacter3()
	:mpModel(nullptr)
	, mTag(EZERO)
{
	//�^�X�N���X�g�ɒǉ�
//	CApplication::TaskManager()->Add(this);
	CTaskManager::Instance()->Add(this);
}

CCharacter3::CCharacter3(int priority)
	:mpModel(nullptr)
	, mTag(EZERO)
{
	mPriority = priority;
	CTaskManager::Instance()->Add(this);
}

CCharacter3::ETag CCharacter3::Tag()
{
	return mTag;
}

CCharacter3::~CCharacter3()
{
	//�^�X�N���X�g����폜
//	CApplication::TaskManager()->Remove(this);
	CTaskManager::Instance()->Remove(this);
}

void CCharacter3::Model(CModel* m)
{
	mpModel = m;
}

//�`�揈��
void CCharacter3::Render()
{
	mpModel->Render(mMatrix);
}
