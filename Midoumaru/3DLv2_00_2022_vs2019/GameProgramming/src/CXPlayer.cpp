#include"CXPlayer.h"
#include"CKey.h"
#include"CXCharacter.h"
#include"CMatrix.h"
#include"CVector.h"
#include"CTransform.h"
#include"CCollisionManager.h"
#include"CTaskManager.h"
#include"CColliderCapsule.h"
#include"CSingleMagic.h"
#include"CAreaMagic.h"
#include "CInput.h"
#include"CCollision.h"
#include"CEffect.h"

#define MODEL_MagicRingRed "res\\MagicRingRed.obj","res\\MagicRingRed.mtl"
#define TURN_V 10.0f	//回転速度
CXPlayer* CXPlayer::spInstance = nullptr;
bool CXPlayer::BattleSwitch = true;

CXPlayer::CXPlayer()
	: mColCapBody(this, nullptr, CVector(0.0f, -100.0f, 20.0f), CVector(0.0f, 65.0f, 0.0f), 0.6f)
	, mColSphereShield(this, nullptr, CVector(0.0f, 0.0f, 0.0f), 0.4f)
	, mColSphereSword(this, nullptr, CVector(-20.0f, 0.0f, 60.0f), 0.5f)
	, mCore(this, nullptr, CVector(0.0f, 0.0f, 10.0f), 0.7f)
	, StandCount(0)
	/*, SlashCount1(0)
	, SlashCount2(0)
	, SlashCount3(0)*/
	, PlayerHp(5)
	, SMagicCount(0)
	, AMagicCount(0)
	, MagicWait(0)
	, MagicRingTime(30)
	, mPushFlg(false)
	, mOldMousePosX(0)
{
	if (mMagicRingRed.Triangles().size() == 0) {
		mMagicRingRed.Load(MODEL_MagicRingRed);
	}
	//タグにプレイヤーを設定します
	mTag = EPLAYER;
	spInstance = this;
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列設定
	mColCapBody.Matrix(&mpCombinedMatrix[14]);      //胴体
	mColSphereShield.Matrix(&mpCombinedMatrix[41]); //盾
	mColSphereSword.Matrix(&mpCombinedMatrix[71]);  //剣
	mCore.Matrix(&mpCombinedMatrix[14]);            //コア
	mColSphereSword.Tag(CCollider::ESWORD);
	mColCapBody.Tag(CCollider::ECORE);
}

void CXPlayer::Update()
{
	//int w = CInput::Wheel();
	StandCount++;

	if (CKey::Push('1')) {
		BattleSwitch = true;
		CXPlayer::ChangeAnimation(1, true, 120);
		StandCount = 0;
	}
	else if (CKey::Push('2')) {
		BattleSwitch = false;
		CXPlayer::ChangeAnimation(12, true, 140);
	}
	

	if (BattleSwitch == true)
	{
		if (CKey::Push(VK_LBUTTON)) {
			CXPlayer::ChangeAnimation(4, false, 92);

			new CEffect(Position() + (CVector(0.0f, 0.0f, 5.0f)), 2.0f, 2.0f,
				"tktk_Sword_2L.png", 2, 2, 10);
			StandCount = 0;
		}
		if (mAnimationIndex == 4) {
			if (mAnimationFrameSize <= mAnimationFrame) {
				CXPlayer::ChangeAnimation(1, true, 120);
			}
		}
		else if (CKey::Push(VK_RBUTTON)) {
			CXPlayer::ChangeAnimation(9, false, 55);
			StandCount = 0;
		}
		else {
			/*if (w != 0) {
				if (w > 0) {
					mRotation = mRotation + CVector(0.0f, TURN_V, 0.0f);
				}
				else {
					mRotation = mRotation - CVector(0.0f, TURN_V, 0.0f);
				}
			}*/
			if (CKey::Push('A')) {
				//CXPlayer::ChangeAnimation(7, true, 23);
				mRotation = mRotation + CVector(0.0f, 2.0f, 0.0f);
			}
			if (CKey::Push('D')) {
				//CXPlayer::ChangeAnimation(6, true, 26);
				mRotation = mRotation + CVector(0.0f, -2.0f, 0.0f);
			}
			if (CKey::Push('S')) {
				CXPlayer::ChangeAnimation(8, true, 80);
				mPosition = mPosition + (CVector(0.0f, -0.2f, -0.09f) * mMatrixRotate);
				StandCount = 0;
			}
			else if (CKey::Push('W')) {
				CXPlayer::ChangeAnimation(3, true, 53);
				mPosition = mPosition + (CVector(0.0f, -0.2f, 0.15f) * mMatrixRotate);
				StandCount = 0;
			}
			else{
				if (mAnimationIndex == 8 || mAnimationIndex == 3) {
					CXPlayer::ChangeAnimation(1, true, 120);
				}
			}	
		}
	}
	if (BattleSwitch == false){
		if (SMagicCount > 0) {
			SMagicCount--;
		}
		else if (CKey::Once(VK_LBUTTON)) {
			CXPlayer::ChangeAnimation(10, false, 90);
			
			CSingleMagic* magic = new CSingleMagic(CVector(0.0f, 0.0f, 0.0f) * mMatrix, mRotation, CVector(1.0f, 1.0f, 1.0f));
			magic->Update();
			StandCount = 0;
			SMagicCount = 80;
		}
		if (AMagicCount > 0) {
			AMagicCount--;
		}
		else if (CKey::Once(VK_RBUTTON)) {
			MagicWait--;
			/*if (MagicWait == 0){
				
			}*/
			CXPlayer::ChangeAnimation(11, false, 100);
			CAreaMagic* magic = new CAreaMagic(CVector(0.0f, 0.0f, 2.0f) * mMatrix, mRotation, CVector(1.0f, 1.0f, 1.0f));
			CAreaMagic* magic2 = new CAreaMagic(CVector(1.0f, 0.0f, 2.0f) * mMatrix, mRotation, CVector(1.0f, 1.0f, 1.0f));
			CAreaMagic* magic3 = new CAreaMagic(CVector(-1.0f, 0.0f, 2.0f) * mMatrix, mRotation, CVector(1.0f, 1.0f, 1.0f));
			magic->Update();
			StandCount = 0;
			MagicWait = 50;
			AMagicCount = 130;
		}
		if (mAnimationIndex == 10 || mAnimationIndex == 11) {
			if (mAnimationFrameSize <= mAnimationFrame) {
				CXPlayer::ChangeAnimation(12, true, 110);
			}
		}
		else {
			if (CKey::Push('A')) {
				//CXPlayer::ChangeAnimation(7, true, 23);
				mRotation = mRotation + CVector(0.0f, 2.0f, 0.0f);
			}
			if (CKey::Push('D')) {
				//CXPlayer::ChangeAnimation(6, true, 26);
				mRotation = mRotation + CVector(0.0f, -2.0f, 0.0f);
			}
			if (CKey::Push('S')) {
				CXPlayer::ChangeAnimation(8, true, 80);
				mPosition = mPosition + (CVector(0.0f, -0.2f, -0.09f) * mMatrixRotate);
				StandCount = 0;
			}
			else if (CKey::Push('W')) {
				CXPlayer::ChangeAnimation(3, true, 62);
				mPosition = mPosition + (CVector(0.0f, -0.2f, 0.15f) * mMatrixRotate);
				StandCount = 0;
			}
			else {
				if (mAnimationIndex == 8 || mAnimationIndex == 3) {
					CXPlayer::ChangeAnimation(12, true, 100);
				}
			}
		}
	}

	/*if (mAnimationIndex == 10)
	{
		MagicWait++;
	}*/
	if (mAnimationIndex == 1 && StandCount > 200) {
		CXPlayer::ChangeAnimation(2, true, 212);
	}
	if (PlayerHp == 0){
		CXPlayer::ChangeAnimation(7, false, 118);
	}

	CXCharacter::Update();
	CTransform::Update();
}

void CXPlayer::Collision(CCollider* m, CCollider* o) {
	////自身のコライダタイプの判定
	//switch (m->Type()) {
	//case CCollider::ECAPSULE:
	//	//相手のコライダが三角コライダの時
	//	if (o->Type() == CCollider::ETRIANGLE) {
	//		CVector adjust;//調整用ベクトル
	//		//三角形と線分の衝突判定
	//		if (CCollider::CollisionTriangleLine(o, m, &adjust)){
	//			//位置の更新(mPosition + adjust)
	//			mPosition = mPosition + adjust;
	//			//行列の更新
	//			CTransform::Update();
	//		}
	//	}
	//	if (o->Type() == CCollider::ECAPSULE) {
	//		CVector adjust;//調整用ベクトル
	//		//三角形と線分の衝突判定
	//		if (CCollider::CollisionCapsule(m, o, &adjust)) {
	//			//位置の更新(mPosition + adjust)
	//			mPosition = mPosition + adjust;
	//			//行列の更新
	//			CTransform::Update();
	//		}
	//	}
	//	break;
	//case CCollider::ECORE:
	////コライダのmとyが衝突しているか判定
	//	if (o->Tag() == CCollider::EMUTANTARM ) {
	//		if (CCollider::Collision(m, o)){
	//			PlayerHp--;
	//		}
	//	}
	//	break;
	//}
	CVector adjust;
	if (CCollision::CollisionAll(m, o, &adjust)) {
		if (o->Type() == CCollider::ETRIANGLE) {
			mPosition = mPosition + adjust;
		}
		if (o->Type() == CCollider::ECAPSULE) {
			mPosition = mPosition + adjust;
		}
		if (o->Tag() == CCollider::EMUTANTARM) {
			PlayerHp--;
		}
	}
}

void CXPlayer::Render()
{
	CXCharacter::Render();
	/*if (BattleSwitch == false){
		
	}*/
	if (mAnimationIndex == 10){
		if (10 >= mAnimationFrame >= 0){
			mMagicRingRed.Render(CMatrix().Scale(0.3f, 0.3f, 0.3f) * mMatrix);
		}
	}
}

CXPlayer* CXPlayer::Get()
{
	return spInstance;
}

void CXPlayer::TaskCollision()
{
	mColCapBody.ChangePriority();
	mColSphereShield.ChangePriority();
	mColSphereSword.ChangePriority();
	CCollisionManager::Get()->Collision(&mColCapBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSphereShield, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSphereSword, COLLISIONRANGE);
}


