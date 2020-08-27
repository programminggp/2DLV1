#include "CXPlayer.h"

#include "CKey.h"


CXPlayer::CXPlayer()
: mColSphereBody(this, CVector(), CVector(), CVector(1.0f,1.0f,1.0f), 0.5f)
, mColSphereHead(this, CVector(0.0f, 5.0f, -3.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.5f)
, mColSphereSword(this, CVector(-10.0f, 10.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 0.3f)
{
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//タグにプレイヤーを設定します
	mTag = EPLAYER;
}

void CXPlayer::Update() {
	switch (mAnimationIndex) {
	case 3:
		mColSphereSword.mTag = CCollider::ESWORD;
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(4, false, 30);
		}
		break;
	case 4:
		mColSphereSword.mTag = CCollider::ENONE;
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(0, true, 60);
		}
		break;
	default:
		if (CKey::Push('A')) {
			mRotation.mY += 2;
		}
		if (CKey::Push('D')) {
			mRotation.mY -= 2;
		}

		if (CKey::Push('W')) {
			ChangeAnimation(1, true, 60);
			mPosition = mPosition + CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
			//		mPosition.mZ += 0.1f;
		}
		else {
			ChangeAnimation(0, true, 60);
		}

		if (CKey::Push(' ')) {
			ChangeAnimation(3, false, 30);
		}
	}

	CXCharacter::Update();
}

void CXPlayer::Init(CModelX *model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpCombinedMatrix = &mpCombinedMatrix[8];
	//頭
	mColSphereHead.mpCombinedMatrix = &mpCombinedMatrix[11];
	//剣
	mColSphereSword.mpCombinedMatrix = &mpCombinedMatrix[21];
	mColSphereSword.mTag = CCollider::ENONE;
}
