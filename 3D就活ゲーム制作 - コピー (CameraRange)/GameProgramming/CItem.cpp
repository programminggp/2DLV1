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


	SoundDest.Load("SE\\se_maoudamashii_battle18.wav");//�Đ��ł��Ȃ��H

	if (mItemNumber == 2){//�΂�
		mTag = ESPRING;
		//mScale.mX = 5.0f; mScale.mY = 5.0f; mScale.mZ = 5.0f;
		mColBody.mRadius = 2.5f;
	}
	else if(mItemNumber == 3){//�X�N�����[
		mTag = ESCREW;
	}
	else if (mItemNumber == 4){//�e
		mTag = EGUN;
	}
	else if (mItemNumber == 5){//��
		mTag = EKEY;
		mRotation.mX = 45;
		mRotation.mZ = 45;
	}
	else if (mItemNumber == 7){
		mTag = EBOAT;
	}
}

void CItem::Collision(CCollider *m, CCollider *y){
	if (mItemNumber == 2 || mItemNumber == 3 || mItemNumber == 4 || mItemNumber == 5){//��
		if (CCollider::Collision(m, y)){
			//�A�C�e��No.2�F�o�l
				//�v���C���[�̃W�����v�͏㏸
				//CPlayer::mJumpV0 = 2.3f;
			//�A�C�e��No.3�F�X�N�����[
				//�v���C���[���j����悤�ɂȂ�
				//Player->mCanSwim = true;
			//�A�C�e��No.4�F�e
				//�v���C���[���e�����Ă�悤�ɂȂ�
				//Player->mCanFire = true;

			if (y->mpParent->mTag == CCharacter::EPLAYER){
				printf("Item Get!\n");
				SetEnabled(false);
			}
		}
	}
	else if (mItemNumber == 1) {//��
		if (CCollider::Collision(m, y)){
			//�e�𓖂Ă�ꂽ����ł���
			if (y->mpParent->mTag == CCharacter::EBULLET){
				SoundDest.Play();
				mTargetAmount--;
				SetEnabled(false);
			}
		}
	}
	else if (mItemNumber == 7) {//�{�[�g
		if (CCollider::Collision(m, y)){
			//�v���C���[�ƐڐG��
			if (y->mpParent->mTag == CCharacter::EPLAYER){
				//�v���C���[�ƈꏏ�ɓ����悤�ɂ���
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
		//if (CKey::Push('Q')){//�ł�
		//	mRotation.mY++;
		//}
		//if (CKey::Push('E')){//��
		//	mRotation.mY--;
		//}

		////A�L�[�AD�L�[�������ɓ��͂���Ă��邩
		//if (CKey::Push('A') && CKey::Push('D')){
		//	mADMoveX = 0.0f;
		//}
		//else if (CKey::Push('A')){//A�L�[����
		//	mADMoveX = 0.166f;
		//}
		//else if (CKey::Push('D')){//D�L�[����
		//	mADMoveX = -0.166f;
		//}
		//else{//�ǂ�������͂Ȃ�
		//	mADMoveX = 0.0f;
		//}
		////W�L�[�AS�L�[�������ɓ��͂���Ă��邩
		//if (CKey::Push('W') && CKey::Push('S')){
		//	mWSMoveZ = 0.0f;
		//}
		//else if (CKey::Push('W')){//W�L�[����
		//	mWSMoveZ = 0.166f;
		//}
		//else if (CKey::Push('S')){//S�L�[����
		//	mWSMoveZ = -0.166f;
		//}
		//else{//�ǂ�������͂Ȃ�
		//	mWSMoveZ = 0.0f;
		//}
		//mPosition = CVector(mADMoveX, 0.0f, mWSMoveZ) * mMatrix;
		mPosition = CPlayer::mpPlayer->mPosition;
		mPosition.mY -= 8.0f;
		mRotation = CPlayer::mpPlayer->mRotation;
	}

	if (mItemNumber == 5){//��
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