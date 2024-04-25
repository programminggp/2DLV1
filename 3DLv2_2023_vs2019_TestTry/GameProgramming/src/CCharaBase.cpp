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

// 被ダメージ処理
void CCharaBase::TakeDamage(int damage, CObjectBase* causedObj)
{
}

// 最大ステータスを取得
const CharaStatus& CCharaBase::MaxStatus() const
{
	return mCharaMaxStatus;
}

// 現在のステータスを取得
const CharaStatus& CCharaBase::Status() const
{
	return mCharaStatus;
}

// 攻撃力の強化割合を取得
float CCharaBase::GetAtkBuff()const
{
	return mBaseAttackBuffRatio;
}

float CCharaBase::GetDefBuff(const CVector& attackDir)const
{
	return mBaseDefenseBuffRatio;
}

//　ダメージ量を算出
int CalcDamage(const CCharaBase* attaker, const CCharaBase* defender)
{
	if (attaker == nullptr || defender == nullptr)return 1;

	// 攻撃方向()
	CVector attackDir = (attaker->Position() - defender->Position()).Normalized();

	float atk = attaker->Status().power * attaker->GetAtkBuff();
	float def = defender->Status().defense * defender->GetDefBuff(attackDir);

	// ダメージ量 =（攻撃力÷2）-（防御÷4）
	int damage = (atk * 0.5f) - (def * 0.25f) + 0.5f;
	return std::max(damage, 1);
}
