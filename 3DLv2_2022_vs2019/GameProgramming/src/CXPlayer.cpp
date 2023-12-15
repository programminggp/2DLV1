#define _USE_MATH_DEFINES
#include <math.h>
#include "CXPlayer.h"
#include "CKey.h"
#include "CCollisionManager.h"
#include "CCamera.h"

#define GRAVITY 0.02f	//重力
//#define GRAVITY 0.00f	//重力
#define VELOCITY 0.1f	//移動速度
#define JUMPV0 0.7f		//ジャンプ力
#define TURN 8.0f		//

CModelX CXPlayer::mModel;
CCharacter* CXPlayer::spInstance = nullptr;

#define PLAYER_MODEL "res\\knight\\knight_low.X"

CXPlayer::CXPlayer()
	: mColSphereBody(this, &mMatrix, CVector(0.5f, -1.0f, 0.0f), 1.0f)
	, mColSphereHead(this, &mMatrix, CVector(0.0f, 1.0f, 0.0f), 1.2f)
	, mColSphereSword0(this, &mMatrix, CVector(0.7f, 3.5f, -0.2f), 0.5f)
	, mColSphereSword1(this, &mMatrix, CVector(0.5f, 2.5f, -0.2f), 0.5f)
	, mColSphereSword2(this, &mMatrix, CVector(0.3f, 1.5f, -0.2f), 0.5f)
	, mColLine(this, &mMatrix, CVector(0.0f, -2.5f, 0.0f), CVector(0.0f, 2.5f, 0.0f))//, 1.2f)
	, mJumpV(0.0f)
{
	//モデルが未入力なら読み込み
	if (!mModel.IsLoaded())
	{
		mModel.Load(PLAYER_MODEL);
		mModel.Frames()[0]->TransformMatrix(CMatrix().RotateY(180.0f));
		mModel.SeparateAnimationSet(0, 1380, 1530, "IDLE1");//1
		mModel.SeparateAnimationSet(0, 1380, 1530, "IDLE1");//2
		mModel.SeparateAnimationSet(0, 10, 80, "WALK");//3
		mModel.SeparateAnimationSet(0, 440, 520, "ATTACK1");//4
		mModel.SeparateAnimationSet(0, 1160, 1260, "DEATH1");//5
		mModel.SeparateAnimationSet(0, 380, 430, "JUMP");//6

		mModel.SeparateAnimationSet(0, 90, 160, "WALKBACK");
		mModel.SeparateAnimationSet(0, 170, 220, "RUN");
		mModel.SeparateAnimationSet(0, 230, 300, "LEFT");
		mModel.SeparateAnimationSet(0, 300, 370, "RIGHT");
//		mModel.SeparateAnimationSet(0, 380, 430, "JUMP");
//		mModel.SeparateAnimationSet(0, 440, 520, "ATTACK1");
		mModel.SeparateAnimationSet(0, 520, 615, "ATTACK2");
		mModel.SeparateAnimationSet(0, 615, 795, "ATTACK3");
		mModel.SeparateAnimationSet(0, 795, 850, "ATTACK4");	//10
		mModel.SeparateAnimationSet(0, 850, 970, "ATTACK5");
		mModel.SeparateAnimationSet(0, 970, 1040, "ATTACK6");
		mModel.SeparateAnimationSet(0, 1040, 1080, "HIT1");
		mModel.SeparateAnimationSet(0, 1080, 1120, "HIT2");
		mModel.SeparateAnimationSet(0, 1120, 1160, "HIT3");	//15
//		mModel.SeparateAnimationSet(0, 1160, 1260, "DEATH1");
		mModel.SeparateAnimationSet(0, 1270, 1370, "DEATH2");
//		mModel.SeparateAnimationSet(0, 1380, 1530, "IDLE1");
		mModel.SeparateAnimationSet(0, 1530, 1830, "IDLE2");
		mModel.SeparateAnimationSet(0, 1830, 1930, "EMOTION1");	//20
		mModel.SeparateAnimationSet(0, 1930, 2040, "EMOTION2");
	}

	//親クラスの初期化
	CXCharacter::Init(&mModel);

	spInstance = this;
	//タグにプレイヤーを設定します
	mTag = EPLAYER;
	mColSphereSword0.Tag(CCollider::EWEAPON);
	mColSphereSword1.Tag(CCollider::EWEAPON);
	mColSphereSword2.Tag(CCollider::EWEAPON);
	mColLine.Tag(CCollider::EBODY);

	//mState = EIDLE;
	//ChangeAnimation(EIDLE, true, 150);
	ChangeState(EIDLE);
}

CXPlayer::CXPlayer(const CVector& pos, const CVector& rot, const CVector& scale)
	: CXPlayer()
{
	mPosition = pos;
	mRotation = rot;
	mScale = scale;
	CTransform::Update();

	//合成行列の設定
	mColSphereBody.Matrix(&mpCombinedMatrix[1]);
	//頭
	mColSphereHead.Matrix(&mpCombinedMatrix[1]);
	//剣
	mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);
	//
	mColLine.Matrix(&mpCombinedMatrix[1]);
}

//void CXPlayer::Init(CModelX* model)
//{
//	CXCharacter::Init(model);
//	//合成行列の設定
//	mColSphereBody.Matrix(&mpCombinedMatrix[1]);
//	//頭
//	mColSphereHead.Matrix(&mpCombinedMatrix[1]);
//	//剣
//	mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
//	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
//	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);
//
//}

void CXPlayer::Update()
{
	switch (mState)
	{
	case EIDLE:
		Idle();
		break;
	case EWALK:
		Walk();
		break;
	case EATTACK:
		Attack();
		break;
	case EJUMP:
		Jump();
		break;
	default:
		;
	}
	//重力
	mJumpV -= GRAVITY;
	mPosition.Y( mPosition.Y() + mJumpV );
#ifdef _DEBUG
	//if (mPosition.Y() < 0.0f)
	//{
	//	if (mState == EJUMP)
	//	{
	//		ChangeState(EIDLE);
	//	}
	//	mPosition.Y(0.0f);
	//	mJumpV = 0.0f;
	//}
#endif
	CXCharacter::Update();
	CCamera::Get()->Position(mPosition + CVector(0.0f, 4.0f, 0.0f));
	mColLine.Update();
	mColSphereHead.Update();
	mColSphereBody.Update();
	mColSphereSword0.Update();
	mColSphereSword1.Update();
	mColSphereSword2.Update();
}

void CXPlayer::TaskCollision()
{
	//mColLine.ChangePriority();
	//mColSphereBody.ChangePriority();
	//mColSphereSword0.ChangePriority();
	//mColSphereSword1.ChangePriority();
	//mColSphereSword2.ChangePriority();
	//CCollisionManager::Get()->Collision(&mColLine, 20);
	CCollisionManager2::Instance()->TM(&mColSphereBody)->Collision(&mColSphereBody);
	CCollisionManager2::Instance()->TM(&mColLine)->Collision(&mColLine);

}

void CXPlayer::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::ECAPSUL:
		if (o->Type() == CCollider::ECAPSUL)
		{
			CVector ad;
			if (CCollider::CollisionCapsule(m, o, &ad))
			{
				//当たらない位置まで下がる
				mPosition = mPosition + ad;
			}
		}
		break;
	case CCollider::ELINE:
		//地面、壁との衝突判定
//		if (o->Tag() == CCollider::EGROUND)
		if (o->Type() == CCollider::ETRIANGLE)
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
	case CCollider::ESPHERE:
		//地面、壁との衝突判定
		if (o->Type() == CCollider::ETRIANGLE)
		{
			CVector ad;
			if (CCollider::CollisionTriangleSphere(o, m, &ad))
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

void CXPlayer::Idle()
{
	EState state = EIDLE;
	mMove = CVector();
	if (CKey::Push('A'))
	{
		state = EWALK;
		mMove += CCamera::Get()->VectorX();
	}
	if (CKey::Push('D'))
	{
		state = EWALK;
		mMove += CCamera::Get()->VectorX() * -1.0f;
	}
	if (CKey::Push('W'))
	{
		state = EWALK;
		mMove += CCamera::Get()->VectorZ();
	}
	if (CKey::Push('S'))
	{
		state = EWALK;
		mMove += CCamera::Get()->VectorZ() * -1.0f;
	}
	if (CKey::Push('X') && mJumpV == 0.0f)
	{
		state = EJUMP;
		mJumpV = JUMPV0;
	}
	if (CKey::Push(' '))
	{
		state = EATTACK;
		mAttackPower = 1.5f;
	}
	//移動
	if (mMove.Length() > 0.0f)
	{
		mMove = mMove.Normalize();
	}
	mPosition = mPosition + mMove * VELOCITY;
	//移動方向へ回転
	CVector forward(sinf(mRotation.Y() / 180.0f * M_PI), 0.0f, cosf(mRotation.Y() / 180.0f * M_PI));
	CVector cross = forward.Cross(mMove); //左右判定　＋左　−右
	float dot = forward.Dot(mMove); //前後の度合（cos値）
	if (cross.Y() > 0.0f)
	{
		mRotation.Y(mRotation.Y() + TURN * (1 - dot));
	}
	else if (cross.Y() < -0.0f)
	{
		mRotation.Y(mRotation.Y() - TURN * (1 - dot));
	}
	//ステータス設定
	ChangeState(state);
}

void CXPlayer::Walk()
{
	Idle();
}

void CXPlayer::Attack()
{
	if (IsAnimationFinished())
	{
		ChangeState(EIDLE);
	}
}

void CXPlayer::Jump()
{
	mPosition = mPosition + mMove * VELOCITY;
	if (CKey::Push(' '))
	{
		ChangeState(EATTACK);
	}
}

void CXPlayer::ChangeState(EState state)
{
	if (mState == state) return;
	mState = state;
	switch(state)
	{
	case EIDLE:
		ChangeAnimation(EIDLE, true, 150);
		break;
	case EWALK:
		ChangeAnimation(EWALK, true, 70);
		break;
	case EATTACK:
		ChangeAnimation(EATTACK, false, 50);
		break;
	case EJUMP:
		ChangeAnimation(EJUMP, false, 70);
		break;
	}
}
