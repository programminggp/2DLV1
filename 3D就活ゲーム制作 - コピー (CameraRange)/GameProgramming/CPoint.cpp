#include "CPoint.h"
CPoint::CPoint()
	: mCollider(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.0f)
	, mpNext(nullptr)
{
	/*mpPoint = this;*/
	mTag = EPOINT;//タグをポイントにする
	mScale = CVector(1.0f, 1.0f, 1.0f);
}
void CPoint::Set(const CVector& pos, float r, CPoint* next) {
	mpNext = next;
	mPosition = pos;
	mCollider.mRadius = r;
	mTag = EPOINT;//タグをポイントにする
	CCharacter::Update();
}
CPoint::CPoint(const CVector& pos, float r, CPoint* next)
	: mCollider(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), r)
{
	Set(pos, r, next);
	//mPosition = pos;
	//mCollider.mRadius = r;
	//mTag = EPOINT;//タグをポイントにする
	//CCharacter::Update();
}
//次のポイントの取得
CPoint* CPoint::GetNextPoint()
{
	return mpNext;
}

#ifdef _DEBUG
#include "CSceneRace.h"
void CPoint::Render()
{
	if (mpNext)
	{
		if (CSceneRace::mPutCol)
		{
			mCollider.Render();
		}
	}
}
#endif
