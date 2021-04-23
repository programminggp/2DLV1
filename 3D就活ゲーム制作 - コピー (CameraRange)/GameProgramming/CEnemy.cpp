#include "CEnemy.h"
#include "CKey.h"

#include "CItem.h"
#include "CBullet.h"
#include "CSceneTitle.h"

//��������������C���N���[�h�Q
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//�Փˎ��̃G�t�F�N�g�ǉ�
#include "CEffect.h"
extern std::shared_ptr<CTexture> TextureExp;
extern std::shared_ptr<CTexture> TextureHit;
extern std::shared_ptr<CTexture> TextureBoost;
#include "CTaskManager.h"

extern CSound SoundBoost;
extern CSound SoundEngine;
extern CSound SoundCollision;
extern CSound SoundCollisionSmall;
extern CSound SoundRespawn;
extern CSound SoundRespawn2;

int CEnemy::RenderType;

CEnemy *CEnemy::mpEnemy = 0;

#define G (9.8f / 90.0f)//�d�͉����x//60.0f
#define JUMPV0 (4.0f*4.0f)//�W�����v����//4.0f

#define MAXSPEED 20.0f //4.5f+3.0f//-0.5f//�Ԃ̍ō����x //�ꉞ�v���C���[���ǂ�������x�ɍō����͏������
#define MAXSPEED_BACK 1.0f*2 *2//�Ԃ̌�ނ���ő呬�x
#define CAR_POWER 0.05f*2 //*2//1�t���[���ӂ�̎Ԃ̉������Ă�����
#define CAR_BREAK_POWER 0.025f*2 *2//�O�i���̃u���[�L�̋���

#define DECELERATE 0.05f*2 //�Ԃ̌��������
#define FIX_ANGLE_VALUE 0.5f*2 //�p�x��0�x�Ɍ����Ē���������(���X�EZ�p)
#define JUMPER01_POWER 3.0f //�W�����v��1�ł̃W�����v��

//#define MAXSPEED 7.0f //�Ԃ̍ō����x
//#define MAXSPEED_BACK 2.0f //�Ԃ̌�ނ���ő呬�x
//#define CAR_POWER 0.1f //1�t���[���ӂ�̎Ԃ̉������Ă�����
//#define CAR_BREAK_POWER 0.05f //�O�i���̃u���[�L�̋���
//
//#define DECELERATE 0.1f //�Ԃ̌��������
//#define FIX_ANGLE_VALUE 0.5f //�p�x��0�x�Ɍ����Ē���������(���X�EZ�p)

CEnemy::CEnemy()
//�ԑ̂�Y���W��0.0f�ɂ������񂾂��ǁE�E�E
//0.0f�ɂ�����ԑ̂������Ă�悤�Ɍ����Ă��܂�
:mColBody(this, CVector(0.0f, 4.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 3)
, mColTire(this, CVector(0.0f, -16.0f + 15.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 3)
, mSearch(this, CVector(0.0f, 20.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 15)
{
	srand(time(NULL));

	mpEnemy = this;

	mScale = CVector(2.5f * 3, 2.5f * 3, 2.5f * 3);

	mVelocityJump = 0.0f;
	mJumpV0 = 1.1f;//�o�l�擾���2.3f�̗\��
	mMoveSpeed = 0.5f;
	mADMoveX = 0.0f;  mWSMoveZ = 0.0f;
	mCarSpeed = 0.0f;//�Ԃ̑��x�̏�����
	mTurnSpeed = 0.0f;

	mCPULevelSpeed = 0.0f;
	if (CSceneTitle::mDifficulty == 1){
		mCPULevelSpeed = 0.0f;
	}
	else if (CSceneTitle::mDifficulty == 2){
		mCPULevelSpeed = 0.0f;
	}
	else if (CSceneTitle::mDifficulty == 3){
		mCPULevelSpeed = 0.0f;
	}

	//mRotation.mY = -90;

	mCanJump = false;
	CanMove = false;

	mChecks = 0;

	isBoost = false;
	mBoostMaxSpeed = 0.0f;
	mBoostTime = 0;

	mTag = EENEMY;

	//�X�^�[�g�n�_�̍��W��ݒ�;
	mStartPoint[0] = 350.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = -100.0f;

	mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
	CCharacter::Update();

	RenderType = 0;//�`�揈�� 0:�Q�[�����  1:�~�j�}�b�v

	mColBody.mTag = CCollider::EBODY;
	mColTire.mTag = CCollider::ESEARCH;
	mSearch.mTag = CCollider::ESEARCH;

	SoundBoost.Load("SE\\Shortbridge31-3.wav");
	SoundEngine.Load("SE\\SNES-Racing01-02.wav");
	SoundCollision.Load("SE\\bomb1.wav");
	SoundCollisionSmall.Load("SE\\SNES-Racing01-10(Collision).wav");
	SoundRespawn.Load("SE\\nc31154.wav");
	SoundRespawn2.Load("SE\\nc55733.wav");

	isSoundEngine = false;
	
	mPointCnt = 0;//�ŏ��̃|�C���g��ݒ�
	//mpPoint = &mPoint[mPointCnt];//�ڎw���|�C���g�̃|�C���^��ݒ�

	mpPoint = mPoint;
	mVPoint = mpPoint->mPosition;//��ԍŏ��͕��U����

	if (CSceneTitle::mDifficulty == 1){

	}
	else{

	}
	mMaxSpeed_PtoP = 20.0f;

	mRespawnCount = 0;
	mEnemyLap = 1;//�G�̃��b�v�����P���ڂɐݒ肷��
	isTouchGoal = false;
	isEnemyGoaled = false;//�܂��S�[�����ĂȂ���Ԃɂ���
	mGoalTime = 0; mRank = 1;
}

void CEnemy::Update(){	
	//�R�[�X�E�|�C���^�EAI�̋������Ƃɍō����x�𒲐�
	if (CSceneTitle::mMode == 2){
		if (mpPoint == mPoint){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint2){
			mMaxSpeed_PtoP = 10.0f;
		}
		else if (mpPoint == mPoint4){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint6){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint8){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint9){
			mMaxSpeed_PtoP = 15.0f;
		}
		else if (mpPoint == mPoint11){
			mMaxSpeed_PtoP = 14.0f;
		}
		else if (mpPoint == mPoint12){
			mMaxSpeed_PtoP = 13.0f;
		}
		else if (mpPoint == mPoint13){
			mMaxSpeed_PtoP = 10.0f;
		}
		else if (mpPoint == mPoint15){
			mMaxSpeed_PtoP = 18.0f;
		}
		else if (mpPoint == mPoint16){
			mMaxSpeed_PtoP = 14.0f;
		}
		else if (mpPoint == mPoint17){
			mMaxSpeed_PtoP = 15.0f;
		}
		else{
			mMaxSpeed_PtoP = 20.0f;
		}
	}
	else if (CSceneTitle::mMode == 5){
		if (mpPoint == mPoint24){
			mMaxSpeed_PtoP = 10.0f;
		}
		else if (mpPoint == mPoint25){
			mMaxSpeed_PtoP = 5.0f;
		}
		else if (mpPoint == mPoint26){
			mMaxSpeed_PtoP = 5.0f;
		}
		else if (mpPoint == mPoint34){
			mMaxSpeed_PtoP = 17.0f;
		}
		else if (mpPoint == mPoint35){
			mMaxSpeed_PtoP = 15.0f;
		}
		
		else{
			mMaxSpeed_PtoP = 20.0f;
		}
	}
	else{
		mMaxSpeed_PtoP = 20.0f;
	}	

	//�|�C���g�ւ̃x�N�g�������߂�
	//CVector dir = mpPoint->mPosition - mPosition;
	dir = mVPoint - mPosition;
	//�������ւ̃x�N�g�������߂�
	left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);

	//�u�[�X�g�c�莞��
	if (mBoostTime > 0){
		mBoostTime--;
	}
	else{
		isBoost = false;
	}
	//�u�[�X�g�L����
	if (isBoost){
		mBoostMaxSpeed = 10.0f;

		if (mCarSpeed < MAXSPEED + mBoostMaxSpeed){
			//�u�[�X�g���̃A�N�Z�����ʂ͎���3�{
			mCarSpeed += CAR_POWER;
			mCarSpeed += CAR_POWER;
		}
	}
	//�u�[�X�g���؂�Ă��鎞
	else{
		//�ō����x���ʏ�܂Ō���
		if (mBoostMaxSpeed > 0.0f){
			if (mBoostMaxSpeed > 0.2f){
				mBoostMaxSpeed -= 0.2f;
			}
			else{
				mBoostMaxSpeed = 0.0f;
			}
		}
		//�u�[�X�g���I�����Č��݂̑��x���ō����x�𒴉߂��Ă����ꍇ�A�ō����x�ɍ��킹�Č�������Ă���
		if (mCarSpeed > MAXSPEED + mBoostMaxSpeed){
			mCarSpeed = MAXSPEED + mBoostMaxSpeed;
		}
	}


	if (CKey::Push(VK_UP) && CanMove && mCarSpeed < mMaxSpeed_PtoP || mChecks >= 0 && CanMove && mCarSpeed < mMaxSpeed_PtoP){
		if (mCarSpeed < MAXSPEED + mBoostMaxSpeed){
			/*if (left.Dot(dir) > -5.0f && left.Dot(dir) < 5.0f){
				mCarSpeed += CAR_POWER;
			}*/
			mCarSpeed += CAR_POWER;
		}
	}
	/*else if (CKey::Push(VK_DOWN) && CanMove || left.Dot(dir) < -5.0f && CanMove || left.Dot(dir) > 5.0f && CanMove)*/
	else if (CKey::Push(VK_DOWN) && CanMove){
		if (mCarSpeed > -MAXSPEED_BACK){
			mCarSpeed -= CAR_POWER;
			//�O�i���Ȃ�u���[�L��������A���߂Ɏ~�܂�
			if (mCarSpeed >= CAR_BREAK_POWER){
				mCarSpeed -= CAR_BREAK_POWER;
			}
		}
	}
	else{
		//�O�i��
		if (mCarSpeed > 0.0f){
			//�����l�Ń}�C�i�X�ɂȂ�Ȃ��悤�ɒ���
			if (mCarSpeed < DECELERATE){
				mCarSpeed = 0.0f;
			}
			else{
				mCarSpeed -= DECELERATE;
			}
		}
		//��ޒ�
		else if (mCarSpeed < 0.0f){
			if (mCarSpeed > -DECELERATE){
				mCarSpeed = 0.0f;
			}
			else{
				mCarSpeed += DECELERATE;
			}
		}
	}

	////�v���C���[��X�p�x��0�ɖ߂���Ă���
	//if (mRotation.mX > 0.0f){
	//	if (mRotation.mX > FIX_ANGLE_VALUE){
	//		mRotation.mX -= FIX_ANGLE_VALUE;
	//	}
	//	else{
	//		mRotation.mX = 0.0f;
	//	}
	//}
	//else if (mRotation.mX < 0.0f){
	//	if (mRotation.mX < -FIX_ANGLE_VALUE){
	//		mRotation.mX += FIX_ANGLE_VALUE;
	//	}
	//	else{
	//		mRotation.mX = 0.0f;
	//	}
	//}
	////�v���C���[��Z�p�x��0�ɖ߂���Ă���
	//if (mRotation.mZ > 0.0f){
	//	if (mRotation.mZ > FIX_ANGLE_VALUE){
	//		mRotation.mZ -= FIX_ANGLE_VALUE;
	//	}
	//	else{
	//		mRotation.mZ = 0.0f;
	//	}
	//}
	//else if (mRotation.mZ < 0.0f){
	//	if (mRotation.mZ < -FIX_ANGLE_VALUE){
	//		mRotation.mZ += FIX_ANGLE_VALUE;
	//	}
	//	else{
	//		mRotation.mZ = 0.0f;
	//	}
	//}
	
	////���E�̉�]����(Y��)
	//if (left.Dot(dir) > 0.0f){
	//	mRotation.mY += 0.3f * 100;
	//}
	//else if (left.Dot(dir) < 0.0f){
	//	mRotation.mY -= 0.3f * 100;
	//}

	//�ړI�n�������ɂ���A����\�Ȏ�
	if (left.Dot(dir) > 0.0f && CanMove){ //�n���h�������ɁI
		//mRotation.mY++;
		if (mTurnSpeed >= 0.0f&&mTurnSpeed<0.5f){
			mTurnSpeed = 0.5f;
		}
		if (mTurnSpeed < 0.0f){
			mTurnSpeed += 0.11f;
		}
		mTurnSpeed += 0.04f;
	}
	//���邢�͖ړI�n���E���ʂŁA����\�Ȏ�
	else if (left.Dot(dir) < 0.0f && CanMove){//�n���h�����E�ɁI
		//mRotation.mY--;
		if (mTurnSpeed <= 0.0f&&mTurnSpeed>-0.5f){
			mTurnSpeed = -0.5f;
		}
		if (mTurnSpeed > 0.0f){
			mTurnSpeed -= 0.11f;
		}
		mTurnSpeed -= 0.04f;
	}
	else{
		if (mTurnSpeed > 0.0f){
			mTurnSpeed -= 0.05f;
		}
		else if (mTurnSpeed < 0.0f){
			mTurnSpeed += 0.05f;
		}
		if (mTurnSpeed<0.04f && mTurnSpeed>-0.04f){
			mTurnSpeed = 0.0f;
		}
	}
	if (mTurnSpeed > 1.0f){
		mTurnSpeed = 1.0f;
	}
	else if (mTurnSpeed < -1.0f){
		mTurnSpeed = -1.0f;
	}
	mRotation.mY += mTurnSpeed;

	if (mRotation.mZ > 180){
		mRotation.mZ = -180;
	}
	else if (mRotation.mZ < -180){
		mRotation.mZ = 180;
	}

	//�O�ɎԂ��i��ł��鎞
	if (mCarSpeed > 0.0f){
		if (isSoundEngine == false){
			//SoundEngine.Repeat();
			isSoundEngine = true;
		}
	}
	//�Ԃ���~���Ă��鎞
	else if (mCarSpeed == 0.0f){
		//SoundEngine.Stop();
		isSoundEngine = false;
	}
	//�Ԃ��o�b�N���Ă��鎞
	else if (mCarSpeed < 0.0f){
		if (isSoundEngine == false){
			//�o�b�N�͈Ⴄ����炷�\��
			//SoundEngine.Repeat();
			isSoundEngine = true;
		}
	}
	//X,Z�����̈ړ���Y������(�d��)�̈ړ��͕ʁX�ɍs��
	mPosition = CVector(mADMoveX, 0.0f, mWSMoveZ + mCarSpeed) * mMatrixRotate * mMatrixTranslate;
	CCharacter::Update();
	//��ɒn�ʂɑ΂��Đ����ɗ���
	//mPosition = CVector(0.0f, mVelocityJump, 0.0f) * mMatrix;//�ł��ĂȂ�
	mPosition = CVector(0.0f, mVelocityJump*2.0f, 0.0f) * //mMatrixScale * 
		CMatrix().RotateZ(0) *
		CMatrix().RotateX(0) *
		CMatrix().RotateY(0)
		*mMatrixTranslate;//�ł��Ă�H
	//mMatrix = mMatrixScale * mMatrixRotate * mMatrixTranslate;

	//�R�[�X�A�E�g������
	/*���s� �����̓G�������Ƀ��X�|�[�����A��̂�������Ƀ��X�|�[�����A���̓G��������*/
	if (mPosition.mY < -700.0f){
		//�����̐�����0�ɂ���
		mVelocityJump = 0.0f;
		//�Ԃ̑��x��0��
		mCarSpeed = 0.0f;
		////���X�^�[�g���̌��ʉ�
		//int sr = rand() % 2;
		//if (sr == 0){
		//	SoundRespawn.Play();
		//}
		//else{
		//	SoundRespawn2.Play();
		//}
		//mRespawnCount++;
		//printf("%d-%d\n",33*mRespawnCount,4*mRespawnCount);
		mRotation = CVector(0.0f, 0.0f, 0.0f);
		if (CSceneTitle::mMode == 1){
			if (mChecks == 0){
				//�X�^�[�g�������̈ʒu�A�����ɖ߂����
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mRotation.mY = 0.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(-80.0f, mStartPoint[1], 2175.0f);
				mRotation.mY = -55.0f;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1620.0f, mStartPoint[1], 450.0f);
				mRotation.mY = -175.0f;
			}
			else if (mChecks == 3){
				mPosition = CVector(-1212.0f, mStartPoint[1], -1616.0f);
				mRotation.mY = 120.0f;
			}
		}
		else if (CSceneTitle::mMode == 2){
			if (mChecks == 0){
				//�X�^�[�g�������̈ʒu�A�����ɖ߂����
				mPosition = CVector(2222.0f, -13.538f, -2510.0f - 30.0f);
				mRotation.mY = 0.0f;
				//�ڕW�n�_���߂�
				mpPoint = mPoint;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 1){
				mPosition = CVector(2893.0f, mStartPoint[1], 2473.0f);
				mRotation.mY = -59.0f;
				mpPoint = mPoint5;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1020.0f, mStartPoint[1], 4594.0f);
				mRotation.mY = -506.4f;
				mpPoint = mPoint10;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 3){
				mPosition = CVector(-1357.0f, mStartPoint[1] - 30.0f, -520.0f);
				mRotation.mY = -200.0f+40.0f;
				mpPoint = mPoint14;
				mVPoint = mpPoint->mPosition;
			}
		}
		else if (CSceneTitle::mMode == 3){
			if (mChecks == 0){
				//�X�^�[�g�������̈ʒu�A�����ɖ߂����
				mPosition = CVector(0.0f, -13.538f, 80.0f);
				mRotation.mY = 90.0f;
				//�ڕW�n�_���߂�
				mpPoint = mPoint;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 1){
				mPosition = CVector(1127.4f, mStartPoint[1]+100.0f, -5054.0f);
				mRotation.mY = 270.1f;
				mpPoint = mPoint7;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 2){
				/*mPosition = CVector(777.0f, mStartPoint[1], 1925.0f);
				mStartRotation = 405.1f;*/
				mPosition = CVector(777.0f, mStartPoint[1], 1925.0f);
				mRotation.mY = 405.1f;
				mpPoint = mPoint12;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 3){
				mPosition = CVector(-5861.0f, mStartPoint[1], 1165.0f);
				mRotation.mY = -583.5f;
				mpPoint = mPoint20;
				mVPoint = mpPoint->mPosition;
			}
		}
		else if (CSceneTitle::mMode == 5){
			if (mChecks == 0){
				//�X�^�[�g�������̈ʒu�A�����ɖ߂����
				mPosition = CVector(-3755.5f, 13.5f, 16060.5f);
				mRotation.mY = -145.0f;
				//�ڕW�n�_���߂�
				mpPoint = mPoint;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 1){
				mPosition = CVector(-16054.4f, 4915.0f, -2180.0f);
				mRotation.mY = -174.6f;
				mpPoint = mPoint16;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 2){
				mPosition = CVector(4680.0f, 13.5f, -2027.0f);
				mRotation.mY = 147.2f;
				mpPoint = mPoint27;
				mVPoint = mpPoint->mPosition;
			}
			else if (mChecks == 3){
				mPosition = CVector(14809.0f, 13.5f, 4270.0f);
				mRotation.mY = -9.5f;
				mpPoint = mPoint31;
				mVPoint = mpPoint->mPosition;
			}
		}
		else{
			if (mChecks == 0){
				//�X�^�[�g�������̈ʒu�A�����ɖ߂����
				mPosition = CVector(mStartPoint[0]-300.0f, mStartPoint[1]+400.0f, mStartPoint[2]-0.0f);
				mRotation.mY = 0.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(-80.0f, mStartPoint[1], 2175.0f);
				mRotation.mY = -55.0f;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1620.0f, mStartPoint[1], 450.0f);
				mRotation.mY = -175.0f;
			}
			else if (mChecks == 3){
				mPosition = CVector(-1212.0f, mStartPoint[1], -1616.0f);
				mRotation.mY = 120.0f;
			}
		}		
	}
	CCharacter::Update();

	//�d�͂̉e���𔽉f����
	mVelocityJump -= G;
	
	if (CKey::Push('I')){
		mpPoint->mRotation.mY++;
	}
}

void CEnemy::Collision(CCollider *mc, CCollider *yc){
	//���g�̃R���C�_�^�C�v�̔���
	switch (mc->mType){
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (yc->mType == CCollider::ETRIANGLE){
			//�����̃R���C�_���{�̂̎�
			if (mc->mTag == CCollider::EBODY){
				//�Ő��ʉߒ��̏���
				if (yc->mpParent->mTag == CCharacter::EGRASS){
					CVector aiueo;//���̃x�N�g��
					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
						//�u�[�X�g���ʂ̕����D�悳���
						if (isBoost == false){
							//printf("speed down�c\n");
							//��葬�x�܂ŃX�s�[�h�ቺ
							if (mCarSpeed > 3.2f + 1.8f){
								if (mCarSpeed > 4.0f + 1.8f){
									mCarSpeed -= 0.8f;
								}
								else{
									mCarSpeed = 3.2f + 1.8f;
								}
							}
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT){//���Ԓn�_1
					if (mChecks == 0){
						//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
						CVector aiu;//�����킹�̂��߂����̃x�N�g��
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							mChecks = 1;
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT2){//���Ԓn�_2
					if (mChecks == 1){
						//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
						CVector aiu;//�����킹�̂��߂����̃x�N�g��
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							mChecks = 2;
							//mChecks = 0;
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT3){//���Ԓn�_3
					if (mChecks == 2){
						//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
						CVector aiu;//�����킹�̂��߂����̃x�N�g��
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							mChecks = 3;
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::EGOALPOINT){//�S�[���n�_
					if (mChecks == 3){
						//�e���Ԓn�_��ʉ߂��Ă��Ȃ����1�����肪�Ȃ���Ȃ�
						CVector aiu;//�����킹�̂��߂����̃x�N�g��
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							isTouchGoal = true;
						}
					}
				}
				if (yc->mpParent->mTag == CCharacter::EWATER){
					//�ʉ߉\�A�X�e�[�W1�̐�
				}
				else if (yc->mpParent->mTag == CCharacter::ECLEARWATER){
					//�ʉ߉\�A�X�e�[�W2�̐�
				}
				else if (yc->mpParent->mTag == CCharacter::ECHECKPOINT
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT2
					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT3
					|| yc->mpParent->mTag == CCharacter::EGOALPOINT
					|| yc->mpParent->mTag == CCharacter::EDASHBOARD){
					//�����̃^�O���t�����I�u�W�F�N�g�͒ʉ߉\
				}
				else{
					CVector adjust;//�����p�x�N�g��
					if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
						//�ʒu�̍X�V
						mPosition = mPosition - adjust * -1;
						//�s��̍X�V
						CCharacter::Update();
						if (yc->mpParent->mTag == CCharacter::EWALL){
							//�Փ˂����̂��ǂ������ꍇ�͕ǂɂ͈��������炸����
							//�ǂɂԂ���ƏՓˉ������A�Ԃ���������
							//�������ɏՓ˂Ō����A�x�����̏Փ˂͓��ɕω��Ȃ�
							if (mCarSpeed > 6.5f){
								mCarSpeed = 2.0f;
								//SoundCollision.Play();
								//���ˎ��A�G�t�F�N�g����
								new CEffect(mPosition + CVector(0.0f, 35.0f, 0.0f), 100.0f, 100.0f, TextureExp, 4, 4, 1, 0);
							}
							else if (mCarSpeed > 4.0f){
								mCarSpeed = 2.0f;
								//SoundCollisionSmall.Play();
								//�y���Ԃ��������G�t�F�N�g����
								new CEffect(mPosition + CVector(0.0f, 15.5f, 0.0f), 60.0f, 60.0f, TextureHit, 3, 8, 1, 1);
							}
							else{
								//�ǂɂ�����Ȃ���̈ړ����A���x���x���Ȃ�
								if (mCarSpeed > 2.0f){
									mCarSpeed = 2.0f;
								}
							}
							//mCarSpeed = -mCarSpeed * 1.0;
							//mVelocityJump = 2.0f;

						}
						else if (yc->mpParent->mTag == CCharacter::EJUMPER){//�W�����v��ɐڐG������
							//mVelocityJump = 0; 
							mVelocityJump = JUMPER01_POWER;
							mCanJump = true;
							//SoundJump.Play();
						}
						else{
							mVelocityJump = 0;
							mCanJump = true;

							/*yc->mV[0] = yc->mV[0] + CVector(0.0f, 0.5f, 0.0f);
							yc->mV[1] = yc->mV[1] + CVector(0.0f, 0.5f, 0.0f);
							yc->mV[2] = yc->mV[2] + CVector(0.0f, 0.5f, 0.0f);*/

							/*if (mRotation.mX < yc->mpParent->mRotation.mX){
							mRotation.mX++;
							}
							else if (mRotation.mX > yc->mpParent->mRotation.mX){
							mRotation.mX--;
							}*/

							//int rotateofycmx = yc->mpParent->mRotation.mX;
							//rotateofycmx %= 360; //-360�x����360�x�܂ł̐��l�ɕϊ�
							////-235=125 300=-60 -180�x�������A180�x�ȏ�̊p�x��
							//if (rotateofycmx < -180){
							//	rotateofycmx += 360;
							//}
							//else if (rotateofycmx >= 180){
							//	rotateofycmx -= 360;
							//}
							//mRotation.mX = rotateofycmx;
							////if (mRotation.mX < yc->mpParent->mRotation.mX){
							////	mRotation.mX = yc->mpParent->mRotation.mX;
							////}
							////else if (mRotation.mX > yc->mpParent->mRotation.mX){
							////	mRotation.mX = yc->mpParent->mRotation.mX;
							////}
							////mRotation = yc->mpParent->mRotation;
						}
					}
					

				}
			}
			//�����̃R���C�_�����G�R���C�_�̎�
			if (mc->mTag == CCollider::ESEARCH){
				//�������ɏ�������̏���
				if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
					CVector aiueo;//�Ƃ�܃x�N�g��
					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
						if (isBoost == false){
							new CEffect(mPosition + CVector(0.0f, 15.5f, 0.0f), 60.0f, 60.0f, TextureBoost, 3, 5, 1, 1);
						}
						isBoost = true;
						mBoostTime = 45;
					}
				}
			}
		}
		if (yc->mType == CCollider::ESPHERE){
			if (CCollider::Collision(mc, yc)){
				//
				if (mc->mTag == CCollider::EBODY){
					if (yc->mpParent->mTag == CCharacter::EPLAYER
						&& yc->mTag == CCollider::EBODY){
						CVector adjust;//�����p�x�N�g��
						////		//�����m�̏Փ˔���
						if (CCollider::Collision(mc, yc, &adjust)){
							//�ʒu�̍X�V
							mPosition = mPosition - adjust * -1;
							//�s��̍X�V
							CCharacter::Update();
						}
					}
					
					if (yc->mpParent->mTag == CCharacter::EENEMY
						&& yc->mTag == CCollider::EBODY){
						if (mc == yc){
							return;
						}
						CVector adjust;//�����p�x�N�g��
						////		//�����m�̏Փ˔���
						if (CCollider::Collision(mc, yc, &adjust)){
							//�ʒu�̍X�V
							mPosition = mPosition - adjust * -1;
							//�s��̍X�V
							CCharacter::Update();
						}
					}					
				}
				//
				if (mc->mTag == CCollider::ESEARCH){
					//�|�C���^����|�C���^�Ɍ����Ĉړ�����
					if (yc->mpParent->mTag == CCharacter::EPOINT){
						CVector adjust;//�����p�x�N�g��
						//		//�����m�̏Փ˔���
						if (CCollider::Collision(mc, yc, &adjust)){
							//�Փ˂����|�C���^�Ɩڎw���Ă���|�C���^��������
							if (yc->mpParent == mpPoint){
								//�Ƃ肠�������int�t���Ő������Ă���
								int r = (mc->mRadius + yc->mRadius) * 0.8f;
								int gap = (rand() % (r * 2) - r);
								//�GAI��Lv�ɂ�蕪�U�l���ω�
								if (CSceneTitle::mDifficulty == 1){
									r = (mc->mRadius + yc->mRadius) * 0.5f;
									gap = (rand() % (r * 2) - r);
								}
								else if (CSceneTitle::mDifficulty == 2){
									r = (mc->mRadius + yc->mRadius) * 0.4f;
									gap = (rand() % (r * 2) - r);
								}
								else if (CSceneTitle::mDifficulty == 3){
									r = (mc->mRadius + yc->mRadius) * 0.2f;
									gap = (rand() % (r * 2) - r);
								}
								//���̃|�C���g�̃|�C���^��ݒ�
								if (mpPoint == mPoint){
									mVPoint = mPoint2->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint2;
								}
								else if(mpPoint==mPoint2){
									mVPoint = mPoint3->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint3;
								}
								else if (mpPoint == mPoint3){
									mVPoint = mPoint4->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint4;
								}
								else if (mpPoint == mPoint4){
									mVPoint = mPoint5->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint5;
								}
								else if (mpPoint == mPoint5){
									mVPoint = mPoint6->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint6;
								}
								else if (mpPoint == mPoint6){
									mVPoint = mPoint7->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint7;
								}
								else if (mpPoint == mPoint7){
									mVPoint = mPoint8->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint8;
								}
								else if (mpPoint == mPoint8){
									mVPoint = mPoint9->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint9;
								}
								else if (mpPoint == mPoint9){
									mVPoint = mPoint10->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint10;
								}
								else if (mpPoint == mPoint10){
									mVPoint = mPoint11->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint11;
								}
								else if (mpPoint == mPoint11){
									mVPoint = mPoint12->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
									mpPoint = mPoint12;
								}
								else if (mpPoint == mPoint12){
									//�R�[�X2or3�𑖍s�����ŕ��򂷂�
									if (CSceneTitle::mMode == 2 || CSceneTitle::mMode == 3 || CSceneTitle::mMode == 5){
										mVPoint = mPoint13->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint13;
									}
									else{
										mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint;//�|�C���g1�ɖ߂��ă��[�v����
									}									
								}
								//�R�[�X2
								else if (CSceneTitle::mMode == 2){
									if (mpPoint == mPoint13){
										mVPoint = mPoint14->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint14;
									}
									else if (mpPoint == mPoint14){
										mVPoint = mPoint15->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint15;
									}
									else if (mpPoint == mPoint15){
										mVPoint = mPoint16->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint16;
									}
									else if (mpPoint == mPoint16){
										mVPoint = mPoint17->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint17;
									}
									else if (mpPoint == mPoint17){
										mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint;
									}
								}
								//�R�[�X3�ł̓|�C���^�̐����g�������
								else if (CSceneTitle::mMode == 3){
									if (mpPoint == mPoint13){
										mVPoint = mPoint14->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint14;
									}
									else if (mpPoint == mPoint14){
										mVPoint = mPoint15->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint15;
									}
									else if (mpPoint == mPoint15){
										mVPoint = mPoint16->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint16;
									}
									else if (mpPoint == mPoint16){
										mVPoint = mPoint17->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint17;
									}
									else if (mpPoint == mPoint17){
										mVPoint = mPoint18->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint18;
									}
									else if (mpPoint == mPoint18){
										mVPoint = mPoint19->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint19;
									}
									else if (mpPoint == mPoint19){
										mVPoint = mPoint20->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint20;
									}
									else if (mpPoint == mPoint20){
										mVPoint = mPoint21->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint21;
									}
									else if (mpPoint == mPoint21){
										mVPoint = mPoint22->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint22;
									}
									else if (mpPoint == mPoint22){
										mVPoint = mPoint23->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint23;
									}
									else if (mpPoint == mPoint23){
										mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint;
									}
								}
								//�R�[�X5�ł̓|�C���^�̐����g�������
								else if (CSceneTitle::mMode == 5){
									if (mpPoint == mPoint13){
										mVPoint = mPoint14->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint14;
									}
									else if (mpPoint == mPoint14){
										mVPoint = mPoint15->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint15;
									}
									else if (mpPoint == mPoint15){
										mVPoint = mPoint16->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint16;
									}
									else if (mpPoint == mPoint16){
										mVPoint = mPoint17->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint17;
									}
									else if (mpPoint == mPoint17){
										mVPoint = mPoint18->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint18;
									}
									else if (mpPoint == mPoint18){
										mVPoint = mPoint19->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint19;
									}
									else if (mpPoint == mPoint19){
										mVPoint = mPoint20->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint20;
									}
									else if (mpPoint == mPoint20){
										mVPoint = mPoint21->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint21;
									}
									else if (mpPoint == mPoint21){
										mVPoint = mPoint22->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint22;
									}
									else if (mpPoint == mPoint22){
										mVPoint = mPoint23->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint23;
									}
									else if (mpPoint == mPoint23){
										mVPoint = mPoint24->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint24;
									}
									else if (mpPoint == mPoint24){
										mVPoint = mPoint25->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint25;
									}
									else if (mpPoint == mPoint25){
										mVPoint = mPoint26->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint26;

										printf("next->26\n");
									}
									else if (mpPoint == mPoint26){
										mVPoint = mPoint27->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint27;
									}
									else if (mpPoint == mPoint27){
										mVPoint = mPoint28->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint28;
									}
									else if (mpPoint == mPoint28){
										mVPoint = mPoint29->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint29;
									}
									else if (mpPoint == mPoint29){
										mVPoint = mPoint30->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint30;
										printf("next->30\n");
									}
									else if (mpPoint == mPoint30){
										mVPoint = mPoint31->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint31;

										printf("next->31\n");
									}
									else if (mpPoint == mPoint31){
										mVPoint = mPoint32->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint32;

										printf("next->32\n");
									}
									else if (mpPoint == mPoint32){
										mVPoint = mPoint33->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint33;
									}
									else if (mpPoint == mPoint33){
										mVPoint = mPoint34->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint34;
									}
									else if (mpPoint == mPoint34){
										mVPoint = mPoint35->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint35;
									}
									else if (mpPoint == mPoint35){
										mVPoint = mPoint36->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint36;
									}
									else if (mpPoint == mPoint36){
										mVPoint = mPoint37->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint37;
									}
									else if (mpPoint == mPoint37){
										mVPoint = mPoint38->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint38;
									}
									else if (mpPoint == mPoint38){
										mVPoint = mPoint39->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint39;
									}
									else if (mpPoint == mPoint39){
										mVPoint = mPoint40->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint40;

										printf("next->40\n");
									}
									else if (mpPoint == mPoint40){
										mVPoint = mPoint41->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint41;
									}

									else if (mpPoint == mPoint41){
										mVPoint = mPoint42->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint42;
									}
									else if (mpPoint == mPoint42){
										mVPoint = mPoint43->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint43;
									}
									else if (mpPoint == mPoint43){
										mVPoint = mPoint44->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint44;
									}
									else if (mpPoint == mPoint44){
										mVPoint = mPoint45->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint45;
									}
									else if (mpPoint == mPoint45){
										mVPoint = mPoint46->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint46;
									}
									else if (mpPoint == mPoint46){
										mVPoint = mPoint47->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint47;
									}
									else if (mpPoint == mPoint47){
										mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
										mpPoint = mPoint;
									}
								}
							}
						}
					}
				}
			}
		}
		break;
	}
}

void CEnemy::TaskCollision()
{
	mColBody.ChangePriority();
	mColTire.ChangePriority();
	mSearch.ChangePriority();
	CollisionManager.Collision(&mColBody);
	CollisionManager.Collision(&mColTire);
	CollisionManager.Collision(&mSearch);
}

//�U���|�C���g
CPoint *CEnemy::mPoint;
CPoint *CEnemy::mPoint2;
CPoint *CEnemy::mPoint3;
CPoint *CEnemy::mPoint4;
CPoint *CEnemy::mPoint5;
CPoint *CEnemy::mPoint6;
CPoint *CEnemy::mPoint7;
CPoint *CEnemy::mPoint8;
CPoint *CEnemy::mPoint9;
CPoint *CEnemy::mPoint10;
CPoint *CEnemy::mPoint11;
CPoint *CEnemy::mPoint12;
CPoint *CEnemy::mPoint13;
CPoint *CEnemy::mPoint14;
CPoint *CEnemy::mPoint15;
CPoint *CEnemy::mPoint16;
CPoint *CEnemy::mPoint17;
CPoint *CEnemy::mPoint18;
CPoint *CEnemy::mPoint19;
CPoint *CEnemy::mPoint20;
CPoint *CEnemy::mPoint21;
CPoint *CEnemy::mPoint22;
CPoint *CEnemy::mPoint23;
CPoint *CEnemy::mPoint24;
CPoint *CEnemy::mPoint25;
CPoint *CEnemy::mPoint26;
CPoint *CEnemy::mPoint27;
CPoint *CEnemy::mPoint28;
CPoint *CEnemy::mPoint29;
CPoint *CEnemy::mPoint30;
CPoint *CEnemy::mPoint31;
CPoint *CEnemy::mPoint32;
CPoint *CEnemy::mPoint33;
CPoint *CEnemy::mPoint34;
CPoint *CEnemy::mPoint35;
CPoint *CEnemy::mPoint36;
CPoint *CEnemy::mPoint37;
CPoint *CEnemy::mPoint38;
CPoint *CEnemy::mPoint39;
CPoint *CEnemy::mPoint40;
CPoint *CEnemy::mPoint41;
CPoint *CEnemy::mPoint42;
CPoint *CEnemy::mPoint43;
CPoint *CEnemy::mPoint44;
CPoint *CEnemy::mPoint45;
CPoint *CEnemy::mPoint46;
CPoint *CEnemy::mPoint47;

int CEnemy::mPointSize = 0;