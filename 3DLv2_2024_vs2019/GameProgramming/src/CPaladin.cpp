#include "CPaladin.h"
#include "CActionCamera.h"
#include "CCollisionManager.h"

#define PALADIN_MODEL_PATH "res\\paladin\\paladin.x"
//追加のアニメーションセット
#define ANIMATION_IDLE "res\\paladin\\Sword And Shield Idle.x"
#define ANIMATION_WALK "res\\paladin\\Paladin WProp J Nordstrom@Sword And Shield Walk.fbx.x"
#define ANIMATION_ATTACK "res\\paladin\\Sword And Shield Slash.x"
#define ANIMATION_JUMP "res\\paladin\\Sword And Shield Jump.x"

//#define ANIMATION_ATTACKSP1 "res\\paladin\\SwordAndShieldAttack.x"


#define VELOCITY 0.1f

CModelX CPaladin::sModel;

CPaladin::CPaladin()
	: CXCharacter(CCharacter3::ETag::EPLAYER)
	, mColBody(
		this,
		nullptr,
		CVector(0.0f, -60.0f, 0.0f),
		CVector(0.0f, 50.0f, 0.0f),
		0.5f)
	, mColSword(
		this,
		nullptr,
		CVector(10.0f, 15.0f, 5.0f),
		CVector(80.0f, 25.0f, 10.0f),
		0.1f)
{
	if (sModel.IsLoaded() == false)
	{
		sModel.Load(PALADIN_MODEL_PATH);
		//アニメーションの追加
		sModel.AddAnimationSet(ANIMATION_IDLE);
		sModel.AddAnimationSet(ANIMATION_WALK);
		sModel.AddAnimationSet(ANIMATION_ATTACK);
		sModel.AddAnimationSet(ANIMATION_JUMP);
	}
	Init(&sModel);
	mColBody.Matrix(&mpCombinedMatrix[3]);
	mColSword.Matrix(&mpCombinedMatrix[50]);
	ChangeAnimation(0, true, 221);
	mState = EState::EIDLE;
}

CPaladin::CPaladin(const CVector& pos, const CVector& rot, const CVector& scale)
	: CPaladin()
{
	Position(pos);
	Rotation(rot);
	Scale(scale);
}

void CPaladin::Update()
{
	mTargetPosition = mPosition + mAdjust;

	switch (mState)
	{
	case EState::EJUMP:
		Jump();
		break;
	case EState::EIDLE:
		Idle();
		break;
	case EState::EATTACK:
		Attack();
		break;
	case EState::EWALK:
		ChangeAnimation(2, true, 33);
		Walk();
		break;
	}

	if (mState != EState::EIDLE || !mGrounded)
	{
		mVelocityG += mGravity;
		mTargetPosition = mTargetPosition + CVector(0.0f, mVelocityG, 0.0f);

		CVector v = mTargetPosition - mPosition;

		if (v.Length() > 0.001f)
		{
			if (v.Length() < mVelocity)
			{
				mVelocity -= 0.01f;
			}
			else if (mVelocity < VELOCITY)
			{
				mVelocity += 0.01f;
			}
			mPosition = mPosition + v.Normalize() * mVelocity;
		}
		else
		{
			mVelocity = 0.0f;
		}
	}

	CXCharacter::Update();
	mColBody.Update();
	mColSword.Update();

	mGrounded = false;
	mAdjust = CVector();
}

void CPaladin::Collision(CCollider* m, CCollider* o)
{
	CVector adjust;
	switch (m->Type())
	{
	case CCollider::EType::ECAPSULE:
		switch (o->Type())
		{
		case CCollider::EType::ECAPSULE:
			switch (o->ParentTag())
			{
			case CCharacter3::ETag::EENEMY:
					if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
					{
						mAdjust = mAdjust + adjust;
					}
			}
			break;
		case CCollider::EType::ETRIANGLE:
			if (CCollider::CollisionCapsuleTriangle(m, o, &adjust))
			{
				mVelocityG = 0.0f;
				mGrounded = true;
				mAdjust = mAdjust + adjust;
			}
			break;
		}
		break;
	}
}

void CPaladin::Collision()
{
	CCollisionManager::Instance()->Collision(&mColBody, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mColSword, COLLISIONRANGE);
}

void CPaladin::Jump()
{
	ChangeAnimation(1, true, 51);
	if (IsAnimationFinished())
	{
		mState = EState::EIDLE;
	}
}

void CPaladin::Idle()
{
	ChangeAnimation(1, true, 221);
	Walk();
}

void CPaladin::Walk()
{
	//カメラの前方
	CVector cameraZ = CActionCamera::Instance()->VectorZ();
	//カメラの左方向
	CVector cameraX = CActionCamera::Instance()->VectorX();
	//キャラクタの前方
	CVector charZ = mMatrixRotate.VectorZ();
	//XZ平面にして正規化
	cameraZ.Y(0.0f); cameraZ = cameraZ.Normalize();
	cameraX.Y(0.0f); cameraX = cameraX.Normalize();
	charZ.Y(0.0f); charZ = charZ.Normalize();
	//移動方向の設定
	CVector move;
	if (mInput.Key('A')) {
		move = move + cameraX;
	}
	if (mInput.Key('D')) {
		move = move - cameraX;
	}
	if (mInput.Key('W')) {
		move = move + cameraZ;
	}
	if (mInput.Key('S')) {
		move = move - cameraZ;
	}

	//移動あり
	if (move.Length() > 0.0f)
	{
		//遊び
		const float MARGIN = 0.06f;
		//正規化
		move = move.Normalize();
		//自分の向きと向かせたい向きで外積
		float cross = charZ.Cross(move).Y();
		//自分の向きと向かせたい向きで内積
		float dot = charZ.Dot(move);
		//外積がプラスは左回転
		if (cross > MARGIN) {
			mRotation.Y(mRotation.Y() + 5.0f);
		}
		//外積がマイナスは右回転
		else if (cross < -MARGIN) {
			mRotation.Y(mRotation.Y() - 5.0f);
		}
		//前後の向きが同じとき内積は1.0
		else if (dot < 1.0f - MARGIN) {
			mRotation.Y(mRotation.Y() - 5.0f);
		}
		//移動方向へ移動
		mTargetPosition = mTargetPosition + move * VELOCITY;
		mState = EState::EWALK;
	}
	else
	{
		mState = EState::EIDLE;
	}

	if (mInput.Key(VK_LBUTTON))
	{
		mState = EState::EATTACK;
	}

	if (mInput.Key(VK_SPACE))
	{
		mState = EState::EJUMP;
		mVelocityG = 1.0f;
	}
}

void CPaladin::Attack()
{
	ChangeAnimation(3, false, 53);
	if (IsAnimationFinished())
	{
		mState = EState::EIDLE;
	}
}
