#include "CXPlayer.h"
#include "CKey.h"
#include "CActionCamera.h"

#define VELOCITY 0.1f	//移動速度
#define TURN_V 10.0f	//回転速度

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
	//float dotZ =
	//	CActionCamera::Instance()->MatrixRotate().VectorZ().Dot(mMatrixRotate.VectorZ());
	//float dotX =
	//	CActionCamera::Instance()->MatrixRotate().VectorX().Dot(mMatrixRotate.VectorZ());
	float dotZ =
		CActionCamera::Instance()->ModelViewInverse().VectorZ().Dot(mMatrixRotate.VectorZ());
	float dotX =
		CActionCamera::Instance()->ModelViewInverse().VectorX().Dot(mMatrixRotate.VectorZ());
	//float dotZ =
	//	CActionCamera::Instance()->ModelView().VectorZ().Dot(mMatrixRotate.VectorZ());
	//float dotX =
	//	CActionCamera::Instance()->ModelView().VectorX().Dot(mMatrixRotate.VectorZ());

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
		if (CKey::Push('D'))
		{
			if (dotX < 0.0f)
			{
				if (dotZ < 0.0f)
				{
					dotZ = -1.0f;
				}
				else
				{
					dotZ = 1.0f;
				}
			}
			mRotation.Y(mRotation.Y() + TURN_V * dotZ);
			ChangeAnimation(1, true, 60);
			mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
		}
		else if (CKey::Push('A'))
		{
			if (dotX > 0.0f)
			{
				if (dotZ < 0.0f)
				{
					dotZ = -1.0f;
				}
				else
				{
					dotZ = 1.0f;
				}
			}
			mRotation.Y(mRotation.Y() - TURN_V*dotZ);
			ChangeAnimation(1, true, 60);
			mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
		}
		else if (CKey::Push('S'))
		{
			if (dotZ < 0.0f)
			{
				if (dotX < 0.0f)
				{
					dotX = -1.0f;
				}
				else
				{
					dotX = 1.0f;
				}
			}
			ChangeAnimation(1, true, 60);
			mRotation.Y(mRotation.Y() - TURN_V*dotX);
			mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
		}
		else if (CKey::Push('W'))
		{
			if (dotZ > 0.0f)
			{
				if (dotX < 0.0f)
				{
					dotX = -1.0f;
				}
				else
				{
					dotX = 1.0f;
				}
			}
			ChangeAnimation(1, true, 60);
			mRotation.Y(mRotation.Y() + TURN_V*dotX);
			mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
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

	//カメラ処理
	CActionCamera::Instance()->Position(mPosition + CVector(0.0f, 3.0f, 0.0f));
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
