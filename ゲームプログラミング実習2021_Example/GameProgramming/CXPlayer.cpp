#include "CXPlayer.h"
#include "CKey.h"
#include "CCollisionManager.h"

#define GRAVITY 0.02f	//重力
CCharacter* CXPlayer::spInstance = nullptr;

CXPlayer::CXPlayer()
	: mColSphereBody(this, nullptr, CVector(), 0.5f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
	, mColLine(this, &mMatrix,CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 3.5f, 0.0f))
	, mJumpV(0.0f)
#ifdef _DEBUG
	, mColDummy1(nullptr, nullptr, CVector(3.0f, 0.0f, 3.0f), CVector(3.0f, 0.0f, -3.0f), CVector(-3.0f, 0.0f, 3.0f))
	, mColDummy2(nullptr, nullptr, CVector(-3.0f, 0.0f, 3.0f), CVector(3.0f, 0.0f, -3.0f), CVector(-3.0f, 0.0f, -3.0f))
#endif
{
	spInstance = this;
	//タグにプレイヤーを設定します
	mTag = EPLAYER;
	mColSphereSword.mTag = CCollider::ESWORD;
#ifdef _DEBUG
	mColDummy1.mTag = CCollider::EGROUND;
	mColDummy2.mTag = CCollider::EGROUND;
#endif
}

CXPlayer::CXPlayer(const CVector& pos, const CVector& rot, const CVector& scale)
	: CXPlayer()
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
	CTransform::Update();
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpMatrix = &mpCombinedMatrix[9];
	//頭
	mColSphereHead.mpMatrix = &mpCombinedMatrix[12];
	//剣
	mColSphereSword.mpMatrix = &mpCombinedMatrix[22];

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
	else if (mAnimationIndex == 7)
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
			ChangeAnimation(1, true, 60);
			mRotation.mY += 2.0f;
		}
		else if (CKey::Push('D'))
		{
			ChangeAnimation(1, true, 60);
			mRotation.mY -= 2.0f;
		}
		if (CKey::Push('W'))
		{
			ChangeAnimation(1, true, 60);
			mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
		}
		else {
			ChangeAnimation(0, true, 60);
		}

		if (CKey::Push('J') && mJumpV == 0.0f)
		{
			ChangeAnimation(7, false, 45);
			//			ChangeAnimation(7, false, 30);
			mJumpV = 0.5f;
		}
		if (CKey::Push(' '))
		{
			ChangeAnimation(3, true, 30);
		}
	}
	//ジャンプ
	mJumpV -= GRAVITY;
	mPosition.mY += mJumpV;
	CXCharacter::Update();
//	mPosition.Print();
}

void CXPlayer::TaskCollision()
{
	mColLine.ChangePriority();
//	CCollisionManager::Get()->Collision(&mColLine, 30);
	CCollisionManager::Get()->Collision(&mColLine, 0);
}

void CXPlayer::Collision(CCollider* m, CCollider* o)
{
	switch (m->mType)
	{
	case CCollider::ELINE:
		//地面、壁との衝突判定
		if (o->mTag == CCollider::EGROUND)
		{
			CVector ad;
			if (CCollider::CollisionTriangleLine(o, m, &ad))
			{
				//当たらない位置まで下がる
				mPosition = mPosition + ad;
				//着地とする
				mJumpV = 0.0f;
			}
		}
		break;
	}
}
