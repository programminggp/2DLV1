#include "CObj.h"
#include "CItem.h"
#include "CPlayer.h"
#include "CTaskManager.h"

#define DOOR_RANGEOFMOTION 90 //�h�A�̉���
#define DOOR_OPENSPEED 2 //�h�A�̊J�����x
#define ROLLINGSPEED 1.0f //��]���鑫��̉�]���x

#define G (9.8f / 120.0f)//�d�͉����x//60.0f

//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k hascollider:�R���C�_�̐����̗L��(�ݒ肪�Ȃ���ΗL)
CObj::CObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale, bool hascollider)
:mpCollider(0)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	
	mObjNumber = 1;

	if (mObjNumber == 9){
		mTag = EWATER;
	}
	if (mObjNumber >= 18 && mObjNumber <= 20){
		mTag = ECLEARWATER;
	}
	/*if (mObjNumber == 20){
		mTag = ECLEARWATER;
	}*/

	if (mObjNumber == 101){
		//�`�F�b�N�|�C���g
		mTag = ECHECKPOINT;
		CCharacter::isRender = false;//�`�悵�Ȃ�
		//�D��x�ύX
		SetPriority(0);
		CTaskManager::Get()->Remove(this);
		CTaskManager::Get()->Add(this);
	}
	if (mObjNumber == 102){
		//�`�F�b�N�|�C���g
		mTag = ECHECKPOINT2;
		CCharacter::isRender = false;//�`�悵�Ȃ�
		//�D��x�ύX
		SetPriority(0);
		CTaskManager::Get()->Remove(this);
		CTaskManager::Get()->Add(this);
	}
	if (mObjNumber == 103){
		//�`�F�b�N�|�C���g
		mTag = ECHECKPOINT3;
		CCharacter::isRender = false;//�`�悵�Ȃ�
		//�D��x�ύX
		SetPriority(0);
		CTaskManager::Get()->Remove(this);
		CTaskManager::Get()->Add(this);
	}
	if (mObjNumber == 109){
		//�S�[���|�C���g(1�������ƈ�����n�_)
		mTag = EGOALPOINT;
		//�D��x�ύX
		SetPriority(0);
		CTaskManager::Get()->Remove(this);
		CTaskManager::Get()->Add(this);
	}
	if (mObjNumber == 202){
		//�W�����v��
		mTag = EJUMPER;
	}

	if (hascollider == false){
		//�����蔻��𐶐����Ȃ�
		//����ɂ�蓖���蔻��̐��𑝂₷�قǏ������d���Ȃ邱�Ƃ����؂��ꂽ
		//�t�ɓ����蔻��𑝂₳�Ȃ���΂����̂ŁA�K�v�Ȃ������蔻��͂ǂ�ǂ�J�b�g���Ă�����B
	}
	else{
		CCharacter::Update();
		//���f���̎O�p�`�̐����A�R���C�_�̔z����쐬���܂�
		mpCollider = new CCollider[model->mTriangles.size()];
		for (int i = 0; i < model->mTriangles.size(); i++){
			//�R���C�_���O�p�`�R���C�_�Őݒ肵�Ă����܂�
			mpCollider[i].SetTriangle(this,
				model->mTriangles[i].mV[0],
				model->mTriangles[i].mV[1],
				model->mTriangles[i].mV[2]);
			mpCollider[i].ChangePriority();
		}
	}
}
//�f�X�g���N�^
CObj::~CObj(){
	//�R���C�_������΍폜
	if (mpCollider){
		//delete[] �z����폜
		delete[] mpCollider;
	}
}

void CObj::Update(){
	if (mObjNumber == 18){
		//�{�[�g���擾���Ȃ��ƕ\������Ȃ���I
		if (CPlayer::mpPlayer->mHaveBoat == false){
			mScale.mY = 0.0f;
		}
		//�擾����Ε\��������I
		else{
			mScale.mY = 35.7f;
			mRotation.mY += 3;
		}
	}

	if (mObjNumber == 21){//���̔ԍ�
		//��𗬂��u���b�N�H
		mPosition.mX += 0.4f;
		if (mPosition.mX > 200.0f){
			mPosition.mX = -200.0f;
		}
	}
	if (mObjNumber == 25){//�񃌉�
		mRotation.mX += ROLLINGSPEED;
	}
	if (mObjNumber == 26){//�����������Y����]
		mRotation.mY += 0.01f;
	}

	if (mObjNumber == 31){//���̔ԍ�
		//��𗬂��u���b�N�H
		mPosition.mX += 2.5f;
		if (mPosition.mX > 3200.0f){
			mPosition.mX = 0.0f;
		}
	}

	if (mObjNumber == 334){
		mScale.mX += 0.1f;
		mScale.mY += 0.1f;
		mScale.mZ += 0.1f;
	}
	if (mObjNumber == 575){
		mPosition.mX = CPlayer::mpPlayer->mPosition.mX;
		mPosition.mZ = CPlayer::mpPlayer->mPosition.mZ;
		mRotation.mY = CPlayer::mpPlayer->mRotation.mY;
	}

	CCharacter::Update();

	if (mObjNumber == 10){
		if (CItem::mTargetAmount <= 0){
			SetEnabled(false);
		}
	}
	if (mObjNumber == 22){
		if (CPlayer::mpPlayer->mIsGetKey){
			if (mRotation.mY < DOOR_RANGEOFMOTION){
				mRotation.mY += DOOR_OPENSPEED;
				mPosition.mX -= DOOR_OPENSPEED * mScale.mX / DOOR_RANGEOFMOTION;
				mPosition.mZ -= DOOR_OPENSPEED * mScale.mX / DOOR_RANGEOFMOTION;
			}
		}
		else{
			//�h�A���܂�
			if (mRotation.mY > 0.0f){
				mRotation.mY -= DOOR_OPENSPEED;
				mPosition.mX += DOOR_OPENSPEED * mScale.mX / DOOR_RANGEOFMOTION;
				mPosition.mZ += DOOR_OPENSPEED * mScale.mX / DOOR_RANGEOFMOTION;
			}
		}
	}
}