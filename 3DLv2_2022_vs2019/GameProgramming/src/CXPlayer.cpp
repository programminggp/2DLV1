#include "CXPlayer.h"
#include "CKey.h"
#include "CCollisionManager.h"

#define GRAVITY 0.02f	//重力
//#define GRAVITY 0.00f	//重力
#define VELOCITY 0.1f

CModelX CXPlayer::mModel;
CCharacter* CXPlayer::spInstance = nullptr;

#define PLAYER_MODEL "res\\knight\\knight_low.X"

CXPlayer::CXPlayer()
	: mColSphereBody(this, nullptr, CVector(0.5f, -1.0f, 0.0f), 1.0f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 1.0f, 0.0f), 1.2f)
	, mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f)
	, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f)
	, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f)
	, mColLine(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 3.5f, 0.0f))
	, mJumpV(0.0f)
{
	//モデルが未入力なら読み込み
	if (!mModel.IsLoaded())
	{
		mModel.Load(PLAYER_MODEL);
		mModel.Frames()[0]->TransformMatrix(CMatrix().RotateY(180.0f));
		mModel.SeparateAnimationSet(0, 1380, 1530, "IDLE1");//1
		mModel.SeparateAnimationSet(0, 10, 80, "WALK");//2
		mModel.SeparateAnimationSet(0, 440, 520, "ATTACK1");//3
		mModel.SeparateAnimationSet(0, 1160, 1260, "DEATH1");//4
		mModel.SeparateAnimationSet(0, 380, 430, "JUMP");//5

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
	//モデルのポインタを代入
	mpModel = &mModel;
	//親クラスの初期化
	CXCharacter::Init(mpModel);

	spInstance = this;
	//タグにプレイヤーを設定します
	mTag = EPLAYER;
	mColSphereSword0.Tag(CCollider::EWEAPON);
	mColSphereSword1.Tag(CCollider::EWEAPON);
	mColSphereSword2.Tag(CCollider::EWEAPON);

	mState = EIDLE;
	ChangeAnimation(EIDLE, true, 150);
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
	bool keyFlg = false;
	switch (mState)
	{
	case EATTACK:
		if (mAnimationFrame >= mAnimationFrameSize)
		{
			mState = EIDLE;
			ChangeAnimation(EIDLE, true, 150);
		}
		break;
	case EIDLE:
	case EWALK:
		if (CKey::Push('A'))
		{
			keyFlg = true;
			mState = EWALK;
			ChangeAnimation(EWALK, true, 70);
			mRotation.Y(mRotation.Y() + 2.0f);
		}
		if (CKey::Push('D'))
		{
			keyFlg = true;
			mState = EWALK;
			ChangeAnimation(EWALK, true, 70);
			mRotation.Y(mRotation.Y() - 2.0f);
		}
		if (CKey::Push('W'))
		{
			keyFlg = true;
			mState = EWALK;
			ChangeAnimation(EWALK, true, 70);
			mPosition += CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
		}
		if(keyFlg == false) {
			mState = EIDLE;
			ChangeAnimation(EIDLE, true, 150);
		}

	case EJUMP:
		if (CKey::Push('J') && mJumpV == 0.0f)
		{
			mState = EJUMP;
			ChangeAnimation(EJUMP, false, 50);
			//			ChangeAnimation(7, false, 30);
			mJumpV = 0.5f;
		}
		if (CKey::Push(' '))
		{
			mState = EATTACK;
			ChangeAnimation(EATTACK, false, 50);
		}
		break;
	default:
		;
	}
	//ジャンプ
	mJumpV -= GRAVITY;
	mPosition.Y( mPosition.Y() + mJumpV );
#ifdef _DEBUG
	if (mPosition.Y() < 0.0f)
	{
		mPosition.Y(0.0f);
		mJumpV = 0.0f;
	}
#endif
	CXCharacter::Update();
}

void CXPlayer::TaskCollision()
{
	mColLine.ChangePriority();
	mColSphereBody.ChangePriority();
	CCollisionManager::Get()->Collision(&mColLine, 20);
//	CCollisionManager::Get()->Collision(&mColSphereBody, 20);
	//	CCollisionManager::Get()->Collision(&mColLine, 0);
}

void CXPlayer::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::ELINE:
		//地面、壁との衝突判定
		if (o->Tag() == CCollider::EGROUND)
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
		if (o->Tag() == CCollider::EGROUND)
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
