#include "CCharacter.h"
#include "CTaskManager.h"

void CCharacter::Model(CModel *m)
{
	mpModel = m;
}

CCharacter::ETag CCharacter::Tag()
{
	return mTag;
}

CCharacter::EState CCharacter::State()
{
	return mState;
}

const CVector& CCharacter::KnockBack()
{
	return mKnockBack;
}

float CCharacter::AttackPower()
{
	return mAttackPower;
}

//�`�揈��
void CCharacter::Render()
{
	mpModel->Render(mMatrix);
}

CCharacter::~CCharacter() {
	//�^�X�N���X�g����폜
	CTaskManager::Get()->Remove(this);
}

CCharacter::CCharacter()
	: CCharacter(0)
	//: mpModel(nullptr)
	//, mTag(EZERO)
	//, mState(ESTATEZERO)
{
	//�^�X�N���X�g�ɒǉ�
	/*CTaskManager::Get()->Add(this);*/
}

CCharacter::CCharacter(int priority)
	: mpModel(nullptr)
	, mTag(EZERO)
	, mState(ESTATEZERO)
	, mAttackPower(0)
{
	mPriority = priority;
	//�^�X�N���X�g�ɒǉ�
	CTaskManager::Get()->Add(this);
}
