#include "CParticle.h"
#include "CApplication.h"

CParticle::CParticle(CMaterial* mat, CVector& pos, CVector& rot, CVector& sca, CVector& posA, CVector& rotA, CVector& scaA, float alpha, int life, bool b)
	: CBillBoard(pos, 1, 1, 100)
	, mpMaterial(mat)
	, mPositionAdd(posA)
	, mRotationAdd(rotA)
	, mScaleAdd(scaA)
	, mAlpha(alpha)
	, mLife(life)
	, mBillboard(b) 
	, mA(1)
{
//	Set(pos, 1, 1);
	Position(pos);
	Rotation(rot);
	Scale(sca);
	float left = 0.0f;
	//UV右
	float right = 1.0f;
	//UV上
	float top = 0.0f;
	//UV下
	float bot = 1.0f;
	//テクスチャマッピング
	mT[0].UV(CVector(right, top, 0.0f), CVector(left, bot, 0.0f),
		CVector(right, bot, 0.0f));
	mT[1].UV(CVector(left, top, 0.0f), CVector(left, bot, 0.0f),
		CVector(right, top, 0.0f));
}

void CParticle::Update()
{
	if (mBillboard)
	{
		CBillBoard::Update();
	}
	else
	{
		CTransform::Update();
	}
	mPosition = mPosition + mPositionAdd;
	mRotation = mRotation + mRotationAdd;
	mScale = mScale + mScaleAdd;
	mA += mAlpha;
	mpMaterial->Diffuse()[3] = mA;
	mLife--;
	if (mLife < 0)
	{
		mEnabled = false;
	}
}

void CParticle::Render()
{
	if (!mBillboard)
	{
		mMatrix = CApplication::ModelViewInverse().Transpose() * mMatrix;
	}
	CBillBoard::Render(mpMaterial);
}
