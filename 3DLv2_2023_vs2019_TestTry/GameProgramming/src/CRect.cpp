#include "CRect.h"

// コンストラクタ（引数なし）
CRect::CRect()
	: CRect(CVector2::zero, CVector2(100.0f, 100.0f))
{
}

// コンストラクタ（xywh）
CRect::CRect(float x, float y, float w, float h)
	: CRect(CVector2(x, y), CVector2(w, h))
{
}

// コンストラクタ（pos + size）
CRect::CRect(const CVector2& pos, const CVector2& size)
	: mPosition(pos)
	, mSize(size)
{
}

// デストラクタ
CRect::~CRect()
{
}

// 矩形情報の設定
void CRect::Set(float x, float y, float w, float h)
{
	Set(CVector2(x, y), CVector2(w, h));
}

// 矩形情報の設定（CVector2）
void CRect::Set(const CVector2& pos, const CVector2& size)
{
	SetPos(pos);
	SetSize(size);
}

// 矩形の開始位置を設定
void CRect::SetPos(float x, float y)
{
	SetPos(CVector2(x, y));
}

// 矩形の開始位置を設定（CVector2）
void CRect::SetPos(const CVector2& pos)
{
	mPosition = pos;
}

// 矩形の開始位置を取得
const CVector2& CRect::GetPos() const
{
	return mPosition;
}

// 矩形のサイズを設定
void CRect::SetSize(float w, float h)
{
	SetSize(CVector2(w, h));
}

// 矩形のサイズを設定（CVector2）
void CRect::SetSize(const CVector2& size)
{
	mSize = size;
}

// 矩形のサイズを取得
const CVector2& CRect::GetSize() const
{
	return mSize;
}

float CRect::X() const
{
	return mPosition.X();
}

void CRect::X(float x)
{
	mPosition.X(x);
}

float CRect::Y() const
{
	return mPosition.Y();
}

void CRect::Y(float y)
{
	mPosition.Y(y);
}

float CRect::W() const
{
	return mSize.X();
}

void CRect::W(float w)
{
	mSize.X(w);
}

float CRect::H() const
{
	return mSize.Y();
}

void CRect::H(float h)
{
	mSize.Y(h);
}
