#include "CObjectBase.h"
#include "CCollider.h"
#include "Maths.h"

// コンストラクタ
CObjectBase::CObjectBase(ETag tag, ETaskPriority prio, int sortOrder, ETaskPauseType pause)
	: CTask(prio, sortOrder, pause)
	, mTag(tag)
	, mIsEnableCol(true)
	, mDepth(0.0f)
	, mColor(CColor::white)
{
}

// デストラクタ
CObjectBase::~CObjectBase()
{
}

// オブジェクトタグを取得
ETag CObjectBase::Tag() const
{
	return mTag;
}

// 衝突判定を行うか設定
void CObjectBase::SetEnableCol(bool isEnable)
{
	mIsEnableCol = isEnable;
}

// 衝突判定を行うかどうか
bool CObjectBase::IsEnableCol() const
{
	return mIsEnableCol && IsEnable();
}

// カラーを設定
void CObjectBase::SetColor(const CColor& color)
{
	mColor = color;
}

// カラーを取得
const CColor& CObjectBase::GetColor() const
{
	return mColor;
}

// アルファ値設定
void CObjectBase::SetAlpha(float alpha)
{
	mColor.A(Math::Clamp01(alpha));
}

// アルファ値取得
float CObjectBase::GetAlpha() const
{
	return mColor.A();
}

// カメラまでの距離を計算
void CObjectBase::CalcDepth()
{
	CCamera* camera = CCamera::CurrentCamera();
	if (camera == nullptr) return;

	CVector camPos = camera->Position();
	CVector pos = Position();

	mDepth = (camPos - pos).LengthSqr();
}

// カメラからの距離を取得
float CObjectBase::GetDepth() const
{
	return mDepth;
}

// 衝突処理
void CObjectBase::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}