#include "CCharaBase.h"

CCharaBase::CCharaBase(ETag tag, ETaskPriority prio, int sortOrder, ETaskPauseType pause)
	: CObjectBase(tag, prio, sortOrder, pause)
	,mBaseAttackBuffRatio(1.0f)
	,mBaseDefenseBuffRatio(1.0f)
{
	mCharaMaxStatus.Reset();
	mCharaStatus.Reset();
}

CCharaBase::~CCharaBase()
{
}

// ��_���[�W����
void CCharaBase::TakeDamage(int damage, CObjectBase* causedObj)
{
}

// �ő�X�e�[�^�X���擾
const CharaStatus& CCharaBase::MaxStatus() const
{
	return mCharaMaxStatus;
}

// ���݂̃X�e�[�^�X���擾
const CharaStatus& CCharaBase::Status() const
{
	return mCharaStatus;
}

// �U���͂̋����������擾
float CCharaBase::GetAtkBuff()const
{
	return mBaseAttackBuffRatio;
}

float CCharaBase::GetDefBuff(const CVector& attackDir)const
{
	return mBaseDefenseBuffRatio;
}

//�@�_���[�W�ʂ��Z�o
int CalcDamage(const CCharaBase* attaker, const CCharaBase* defender)
{
	if (attaker == nullptr || defender == nullptr)return 1;

	// �U������()
	CVector attackDir = (attaker->Position() - defender->Position()).Normalized();

	float atk = attaker->Status().power * attaker->GetAtkBuff();
	float def = defender->Status().defense * defender->GetDefBuff(attackDir);

	// �_���[�W�� =�i�U���́�2�j-�i�h�䁀4�j
	int damage = (atk * 0.5f) - (def * 0.25f) + 0.5f;
	return std::max(damage, 1);
}
