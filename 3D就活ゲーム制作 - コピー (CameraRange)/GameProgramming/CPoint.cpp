#include "CPoint.h"

CPoint::CPoint()
: mCollider(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.0f)
, mpNext(nullptr)
{
	/*mpPoint = this;*/
	mTag = EPOINT;//�^�O���|�C���g�ɂ���
	mScale = CVector(1.0f, 1.0f, 1.0f);
}
void CPoint::Set(const CVector &pos, float r, CPoint* next){
	mpNext = next;
	mPosition = pos;
	mCollider.mRadius = r;
	mTag = EPOINT;//�^�O���|�C���g�ɂ���
	CCharacter::Update();
}
CPoint::CPoint(const CVector &pos, float r, CPoint* next)
: mCollider(this, CVector(), CVector(), CVector(1.0f, 1.0f, 1.0f), r)
{
	Set(pos, r, next);
	//mPosition = pos;
	//mCollider.mRadius = r;
	//mTag = EPOINT;//�^�O���|�C���g�ɂ���
	//CCharacter::Update();
}
//���̃|�C���g�̎擾
CPoint* CPoint::GetNextPoint()
{
	return mpNext;
}
