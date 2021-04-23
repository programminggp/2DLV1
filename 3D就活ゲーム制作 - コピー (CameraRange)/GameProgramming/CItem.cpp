#include "CItem.h"
#include "CKey.h"
#include "CPlayer.h"

//CItem *CItem::mpItem = 0;

CSound SoundDest;

int CItem::mTargetAmount = 0;

CItem::CItem(CModel *model, CVector position, CVector rotation, CVector scale, int itemnum)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 4.0f)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;

	mItemNumber = itemnum;

	
	if (mItemNumber == 1){
		mTargetAmount++;
	}

	mBoatMove = false;


	SoundDest.Load("SE\\se_maoudamashii_battle18.wav");//再生できない？

	if (mItemNumber == 2){//ばね
		mTag = ESPRING;
		//mScale.mX = 5.0f; mScale.mY = 5.0f; mScale.mZ = 5.0f;
		mColBody.mRadius = 2.5f;
	}
	else if(mItemNumber == 3){//スクリュー
		mTag = ESCREW;
	}
	else if (mItemNumber == 4){//銃
		mTag = EGUN;
	}
	else if (mItemNumber == 5){//鍵
		mTag = EKEY;
		mRotation.mX = 45;
		mRotation.mZ = 45;
	}
	else if (mItemNumber == 7){
		mTag = EBOAT;
	}
}

void CItem::Collision(CCollider *m, CCollider *y){
	if (mItemNumber == 2 || mItemNumber == 3 || mItemNumber == 4 || mItemNumber == 5){//仮
		if (CCollider::Collision(m, y)){
			//アイテムNo.2：バネ
				//プレイヤーのジャンプ力上昇
				//CPlayer::mJumpV0 = 2.3f;
			//アイテムNo.3：スクリュー
				//プレイヤーが泳げるようになる
				//Player->mCanSwim = true;
			//アイテムNo.4：銃
				//プレイヤーが弾を撃てるようになる
				//Player->mCanFire = true;

			if (y->mpParent->mTag == CCharacter::EPLAYER){
				printf("Item Get!\n");
				SetEnabled(false);
			}
		}
	}
	else if (mItemNumber == 1) {//仮
		if (CCollider::Collision(m, y)){
			//弾を当てられたら消滅する
			if (y->mpParent->mTag == CCharacter::EBULLET){
				SoundDest.Play();
				mTargetAmount--;
				SetEnabled(false);
			}
		}
	}
	else if (mItemNumber == 7) {//ボート
		if (CCollider::Collision(m, y)){
			//プレイヤーと接触時
			if (y->mpParent->mTag == CCharacter::EPLAYER){
				//プレイヤーと一緒に動くようにする
				mBoatMove = true;
				/*mPosition.mX = y->mpParent->mPosition.mX;
				mPosition.mZ = y->mpParent->mPosition.mZ;*/
				//mPosition = y->mpParent->mPosition;
			}
		}
	}
}
void CItem::Update(){
	if (mBoatMove){
		//if (CKey::Push('Q')){//でば
		//	mRotation.mY++;
		//}
		//if (CKey::Push('E')){//つぐ
		//	mRotation.mY--;
		//}

		////Aキー、Dキーが同時に入力されているか
		//if (CKey::Push('A') && CKey::Push('D')){
		//	mADMoveX = 0.0f;
		//}
		//else if (CKey::Push('A')){//Aキーだけ
		//	mADMoveX = 0.166f;
		//}
		//else if (CKey::Push('D')){//Dキーだけ
		//	mADMoveX = -0.166f;
		//}
		//else{//どちらも入力なし
		//	mADMoveX = 0.0f;
		//}
		////Wキー、Sキーが同時に入力されているか
		//if (CKey::Push('W') && CKey::Push('S')){
		//	mWSMoveZ = 0.0f;
		//}
		//else if (CKey::Push('W')){//Wキーだけ
		//	mWSMoveZ = 0.166f;
		//}
		//else if (CKey::Push('S')){//Sキーだけ
		//	mWSMoveZ = -0.166f;
		//}
		//else{//どちらも入力なし
		//	mWSMoveZ = 0.0f;
		//}
		//mPosition = CVector(mADMoveX, 0.0f, mWSMoveZ) * mMatrix;
		mPosition = CPlayer::mpPlayer->mPosition;
		mPosition.mY -= 8.0f;
		mRotation = CPlayer::mpPlayer->mRotation;
	}

	if (mItemNumber == 5){//鍵
		mRotation.mY ++;
		if (mRotation.mY > 360){
			mRotation.mY -= 360;
		}
	}


	CCharacter::Update();
}

void CItem::TaskCollision(){
	mColBody.ChangePriority();
	CollisionManager.Collision(&mColBody);
}