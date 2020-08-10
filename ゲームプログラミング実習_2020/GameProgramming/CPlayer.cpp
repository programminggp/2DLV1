#include "CPlayer.h"
#include "CKey.h"
#include "CInput.h"
#include "CSound.h"

//12
#define G (9.8f / 60.0f) //重力加速度
#define JUMPV0 (4.0f)	//ジャンプ初速

extern CSound Sound;

void CPlayer::Update() {
	if (CKey::Push('A')) {
		mRotation.mY++;
	}
	if (CKey::Push('D')) {
		mRotation.mY--;
	}
	//5
	if (CKey::Push('W')) {
		mPosition = CVector(0.0f, 0.0f, 0.5f) * mMatrix;
	}
	//12
	if (CKey::Push('K') && mVelovcityJump <= 0) {
		mAudio.Play();
		mVelovcityJump = JUMPV0;
//		Sound.Play();
	}
	mVelovcityJump -= G;
	mPosition = mPosition + CVector(0.0f, 1.0f, 0.0f) * mVelovcityJump;

	CCharacter::Update();

	if (CInput::GetMouseButton(VK_LBUTTON)) {
		printf("Push Mouse LButton\n");
	}
}

CPlayer::CPlayer()
//コライダの初期設定
: mColBody(this, CVector(0.0f, 4.0f, -1.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 9.0f)
, mVelovcityJump(0.0f)
{
}

void CPlayer::Collision(CCollider *mcol, CCollider *ycol) {
	CVector adjust;
	if (mcol->mType == CCollider::ESPHERE) {
		if (ycol->mType == CCollider::ETRIANGLE) {
			if (CCollider::CollisionTriangleSphere(ycol, mcol, &adjust)) {
				mPosition = mPosition + adjust;
				CCharacter::Update();
				//12
				mVelovcityJump = 0.0f;
			}
		}
	}
}
