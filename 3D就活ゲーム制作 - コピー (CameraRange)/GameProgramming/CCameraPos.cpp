#include "CCameraPos.h"
//#include "CKey.h"

#include "CItem.h"
#include "CSceneTitle.h"

#include "CTaskManager.h"

#include <stdio.h>
#include <math.h>

#define PI 3.141592

CCameraPos *CCameraPos::mpCamera = 0;

#define G (9.8f / 90.0f)//�d�͉����x//60.0f
#define JUMPV0 (4.0f*4.0f)//�W�����v����//4.0f

#define MAXSPEED 20.0f //4.5f+3.0f *5//�Ԃ̍ō����x
#define MAXSPEED_BACK 1.0f*2 *2//�Ԃ̌�ނ���ő呬�x
#define CAR_POWER 0.05f*2 //*2//1�t���[���ӂ�̎Ԃ̉������Ă�����
#define CAR_BREAK_POWER 0.025f*2 *2//�O�i���̃u���[�L�̋���
//#define MAXSPEED_LIMITUP 10.0f //�u�[�X�g���̍ō����x�̏���˔j��

#define DECELERATE 0.05f*2 //�Ԃ̌��������
#define FIX_ANGLE_VALUE 0.5f*2 //�p�x��0�x�Ɍ����Ē���������(���X�EZ�p)

#define JUMPER01_POWER 3.0f;//�W�����v��1�ɂ��W�����v�̋���

//#define MAXSPEED 7.0f //�Ԃ̍ō����x
//#define MAXSPEED_BACK 2.0f //�Ԃ̌�ނ���ő呬�x
//#define CAR_POWER 0.1f //1�t���[���ӂ�̎Ԃ̉������Ă�����
//#define CAR_BREAK_POWER 0.05f //�O�i���̃u���[�L�̋���
//
//#define DECELERATE 0.1f //�Ԃ̌��������
//#define FIX_ANGLE_VALUE 0.5f //�p�x��0�x�Ɍ����Ē���������(���X�EZ�p)

CCameraPos::CCameraPos()
//�ԑ̂�Y���W��0.0f�ɂ������񂾂��ǁE�E�E
//0.0f�ɂ�����ԑ̂������Ă�悤�Ɍ����Ă��܂�
:mColCam(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 3)
{
	mpCamera = this;	

	CanMove = false;	
	mTag = EPLAYER;

	CCharacter::Update();

	mColCam.mTag = CCollider::ECAMERA;

	mPosition = CPlayer::mpPlayer->mPosition;
	mPosition = CCameraRange::mpCameraRange->mPosition;
	//printf("X:%f\nY:%f\nZ:%f\n", mPosition.mX, mPosition.mY, mPosition.mZ);
	mRotation = CPlayer::mpPlayer->mRotation;
	CCharacter::Update();
	mVCamY = 0;
}

void CCameraPos::Update(){	
	mVPoint = CCameraRange::mpCameraRange->mPosition;
	CCharacter::Update();
	//�|�C���g�ւ̃x�N�g�������߂�
	CVector dir = mVPoint - mPosition;
	//�������ւ̃x�N�g�������߂�
	CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	CVector up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
	//������
	while (left.Dot(dir) > 0.0f){
		mRotation.mY++;
		left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	}
	while (left.Dot(dir) < 0.0f){
		mRotation.mY--;
		left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	}
	//�����
	while (up.Dot(dir) > 0.0f){
		mRotation.mX--;
		up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
	}
	while (up.Dot(dir) < 0.0f){
		mRotation.mX++;
		up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
	}
	CCharacter::Update();
	//�v���C���[�̎Ԃ̃X�s�[�h���Βl�ɕω�
	mCameraSpeed = CPlayer::mpPlayer->mCarSpeed;
	if (mCameraSpeed < 0.0f){
		mCameraSpeed *= -1;
	}
	mPosition = CVector(0.0f, 0.0f, mCameraSpeed) * mMatrixRotate * mMatrixTranslate;
	CCharacter::Update();

	if (CPlayer::mpPlayer->isRespawn){
		mPosition = CVector(0.0f, 17.0f, -40.0f) * CPlayer::mpPlayer->mMatrixScale * CPlayer::mpPlayer->mMatrixRotate * CPlayer::mpPlayer->mMatrixTranslate;
		CCharacter::Update();
		CPlayer::mpPlayer->isRespawn = false;
	}
}

void CCameraPos::Collision(CCollider *mc, CCollider *yc){
	//���g�̃R���C�_�^�C�v�̔���
	switch (mc->mType){
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (yc->mType == CCollider::ETRIANGLE){
			//�����̃R���C�_���{�̂̎�
			if (mc->mTag == CCollider::ECAMERA){
				if (yc->mpParent->mTag == CCharacter::EWATER
					|| yc->mpParent->mTag == CCharacter::ECLEARWATER
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT2
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT3
					|| yc->mpParent->mTag == CCharacter::EGOALPOINT					
					|| yc->mpParent->mTag == CCharacter::EDASHBOARD){
					//�����̃p�l���͒ʍs�\
				}
				else{
					CVector adjust;//�����p�x�N�g��
					//		//�O�p�`�Ƌ��̏Փ˔���
					if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
						//�ʒu�̍X�V
						mPosition = mPosition - adjust * -1;
						//�s��̍X�V
						CCharacter::Update();
					}
				}
			}
		}
		break;
	}
}


void CCameraPos::TaskCollision()
{
	mColCam.ChangePriority();
	CollisionManager.Collision(&mColCam);
}