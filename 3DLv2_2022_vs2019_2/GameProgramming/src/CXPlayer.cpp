#include "CXPlayer.h"
#include "CKey.h"

CXPlayer::CXPlayer()
	: mColSphereBody(this, nullptr, CVector(), 0.5f)
	, mColSphereHead(this, nullptr,
		CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColSphereSword(this, nullptr,
		CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{
	//タグにプレイヤーを設定します
	mTag = EPLAYER;
	mColSphereSword.Tag(CCollider::ETag::ESWORD);
}

void CXPlayer::Update()
{
	if (mAnimationIndex == 3)
	{
		if (mAnimationFrame >= mAnimationFrameSize)
		{
			ChangeAnimation(4, false, 30);
		}
	}
	else if (mAnimationIndex == 4)
	{
		if (mAnimationFrame >= mAnimationFrameSize)
		{
			ChangeAnimation(0, true, 60);
		}
	}
	else
	{
		if (CKey::Push('A'))
		{
			mRotation.Y(mRotation.Y() + 2.0f);
		}
		if (CKey::Push('D'))
		{
			mRotation.Y(mRotation.Y() - 2.0f);
		}
		if (CKey::Push('W'))
		{
			ChangeAnimation(1, true, 60);
			//		mPosition = mPosition + CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
			//		mPosition = mPosition + CVector(mMatrixRotate.M()[8], mMatrixRotate.M()[9], mMatrixRotate.M()[10]) * 0.1f;
			mPosition = mPosition + mMatrixRotate.VectorZ() * 0.1f;
		}
		else
		{
			ChangeAnimation(0, true, 60);
		}
		if (CKey::Push(' '))
		{
			ChangeAnimation(3, false, 30);
		}
	}
	CXCharacter::Update();
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.Matrix(&mpCombinedMatrix[9]);
	//頭
	mColSphereHead.Matrix(&mpCombinedMatrix[12]);
	//剣
	mColSphereSword.Matrix(&mpCombinedMatrix[22]);
}
