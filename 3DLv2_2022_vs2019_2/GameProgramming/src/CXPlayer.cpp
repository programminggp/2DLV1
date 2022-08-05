#include "CXPlayer.h"
#include "CKey.h"
#include "CActionCamera.h"

#define VELOCITY 0.1f	//�ړ����x
#define TURN_V 2.0f		//��]���x

CXPlayer::CXPlayer()
	: mColSphereBody(this, nullptr, CVector(), 0.5f)
	, mColSphereHead(this, nullptr,
		CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColSphereSword(this, nullptr,
		CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{
	//�^�O�Ƀv���C���[��ݒ肵�܂�
	mTag = EPLAYER;
	mColSphereSword.Tag(CCollider::ETag::ESWORD);
}

void CXPlayer::Update()
{
	float dotZ =
		CActionCamera::Instance()->MatrixRotate().VectorZ().Dot(mMatrixRotate.VectorZ());
	float dotX =
		CActionCamera::Instance()->MatrixRotate().VectorX().Dot(mMatrixRotate.VectorZ());

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
			if (dotZ > 0.0f)
			{
				mRotation.Y(mRotation.Y() + TURN_V);
			}
			else
			{
				mRotation.Y(mRotation.Y() - TURN_V);
			}
			ChangeAnimation(1, true, 60);
			mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
		}
		else if (CKey::Push('D'))
		{
			if (dotZ > 0.0f)
			{
				mRotation.Y(mRotation.Y() - TURN_V);
			}
			else
			{
				mRotation.Y(mRotation.Y() + TURN_V);
			}
			ChangeAnimation(1, true, 60);
			mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
		}
		else if (CKey::Push('W'))
		{
			ChangeAnimation(1, true, 60);
			if (dotX > 0.0f)
			{
				mRotation.Y(mRotation.Y() - TURN_V);
			}
			else
			{
				mRotation.Y(mRotation.Y() + TURN_V);
			}
			mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
		}
		else if (CKey::Push('S'))
		{
			ChangeAnimation(1, true, 60);
			if (dotX > 0.0f)
			{
				mRotation.Y(mRotation.Y() + TURN_V);
			}
			else
			{
				mRotation.Y(mRotation.Y() - TURN_V);
			}
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

	//�J��������
	CActionCamera::Instance()->Position(mPosition + CVector(0.0f, 3.0f, 0.0f));
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.Matrix(&mpCombinedMatrix[9]);
	//��
	mColSphereHead.Matrix(&mpCombinedMatrix[12]);
	//��
	mColSphereSword.Matrix(&mpCombinedMatrix[22]);
}
