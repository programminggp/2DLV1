#include "CPlayer.h"
#include "CKey.h"

#include "CItem.h"
#include "CBullet.h"
#include "CSceneTitle.h"

//�Փˎ��̃G�t�F�N�g�ǉ�
#include "CEffect.h"
extern std::shared_ptr<CTexture> TextureExp;
extern std::shared_ptr<CTexture> TextureHit;
extern std::shared_ptr<CTexture> TextureBoost;
#include "CTaskManager.h"

#include <stdio.h>
#include <math.h>

#define PI 3.141592

extern CSound SoundJump;
extern CSound SoundShot;
extern CSound SoundItemGet;
extern CSound SoundBoost;
extern CSound SoundEngine;
extern CSound SoundHorn;
extern CSound SoundCollision;
extern CSound SoundCollisionSmall;

CPlayer *CPlayer::mpPlayer = 0;

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

CPlayer::CPlayer()
//�ԑ̂�Y���W��0.0f�ɂ������񂾂��ǁE�E�E
//0.0f�ɂ�����ԑ̂������Ă�悤�Ɍ����Ă��܂�
:mColBody(this, CVector(0.0f, 4.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f*3)
, mColTire(this, CVector(0.0f, -16.0f + 15.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f * 3)
//, mColCamRange(this, CVector(0.0f, 20.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 50.0f)
//, mColCamera(this, CVector(0.0f, 17.0f, 40.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 15.0f * 1)
{
	mpPlayer = this;

	mScale = CVector(7.5f, 7.5f, 7.5f);

	mVelocityJump = 0.0f;
	mJumpV0 = 1.1f;//�o�l�擾���2.3f�̗\��
	mMoveSpeed = 0.5f;
	mADMoveX = 0.0f;  mWSMoveZ = 0.0f;
	mCarSpeed = 0.0f;//�Ԃ̑��x�̏�����
	mTurnSpeed = 0.0f;
	mBuzzerCount = 0;//�u�U�[��炵����
	mRespawnCount = 0;//���X�|�[��������

	mCanJump = false;
	mCanSwim = false;
	mIsGetKey = false;
	mHaveBoat = false;
	mFlyingMode = false;

	CanMove = false;
	isRespawn = false;

	mChecks = 0;

	isBoost = false;
	mBoostMaxSpeed = 0.0f;
	mBoostTime = 0;

	mTag = EPLAYER;
	//mColCamRange.mTag = CCollider::ECAMERA_RANGE;
	mJumpPrio = 0;

	if (CSceneTitle::mMode == 3){
		//�X�^�[�g�n�_�̍��W��ݒ�;
		mStartPoint[0] = 0.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = 80.0f;
		mStartRotation = 90.0f;
		mRotation.mY = mStartRotation;
	}
	else if (CSceneTitle::mMode == 2){
		//�X�^�[�g�n�_�̍��W��ݒ�;
		mStartPoint[0] = 2222.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = -2510.0f;
		mStartRotation = 0.0f;
		mRotation.mY = mStartRotation;
	}
	else if (CSceneTitle::mMode == 4){
		//�X�^�[�g�n�_�̍��W��ݒ�;
		mStartPoint[0] = 0.0f;  mStartPoint[1] = 0.0f;  mStartPoint[2] = 0.0f;
		//mStartPoint[0] = 450.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = -50.0f;
		mStartRotation = 180.0f;
		mRotation.mY = mStartRotation;
	}
	else if (CSceneTitle::mMode == 5){
		//�X�^�[�g�n�_�̍��W��ݒ�;
		mStartPoint[0] = -3755.5f;  mStartPoint[1] = 13.5f;  mStartPoint[2] = 16060.5f;
		mStartRotation = -145.0f;
		mRotation.mY = mStartRotation;		
	}	
	else{
		//�X�^�[�g�n�_�̍��W��ݒ�;
		mStartPoint[0] = 350.0f;  mStartPoint[1] = -13.538f;  mStartPoint[2] = -100.0f;
		mStartRotation = 0.0f;
		mRotation.mY = mStartRotation;
	}
	mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
	CCharacter::Update();
	
	mColBody.mTag = CCollider::EBODY;
	mColTire.mTag = CCollider::ESEARCH;
	//mColCamRange.mTag = CCollider::ECAMERA_RANGE;
	//mColCamera.mTag = CCollider::ECAMERA;

	SoundJump.Load("SE\\jump12.wav");
	SoundShot.Load("SE\\shot1.wav");
	SoundItemGet.Load("SE\\se_maoudamashii_system46.wav");	
	SoundBoost.Load("SE\\Shortbridge31-3.wav");
	SoundEngine.Load("SE\\SNES-Racing01-02.wav");
	SoundEngine_Turf.Load("SE\\SNES-Racing02-02.wav");
	SoundHorn.Load("SE\\car-horn1.wav");
	SoundCollision.Load("SE\\bomb1.wav");
	SoundCollisionSmall.Load("SE\\SNES-Racing01-10(Collision).wav");
	
	
	isSoundEngine = false;
	isTouchGoal = false;
	mGoalTime = 0; mRank = 1;
}

void CPlayer::Update(){
	if (CKey::Once(' ')){//�N���N�V������炷
		SoundHorn.Play();
		mBuzzerCount++;
	}

	
	//��s���[�h�L����(�f�o�b�O�p)
	if (mFlyingMode){
		if (CKey::Push('W')){
			mVelocityJump = mMoveSpeed*3;
		}
		else if (CKey::Push('S')){
			mVelocityJump = -mMoveSpeed*3;
		}
		else{
			mVelocityJump = 0.0f;
		}
	}

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


	if (CKey::Push(VK_UP) && CanMove){
		if (mCarSpeed < MAXSPEED + mBoostMaxSpeed){
			mCarSpeed += CAR_POWER;
		}		
	}
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

	if (CKey::Push(VK_LEFT) && CanMove){ //�n���h�������ɁI
		//mRotation.mY++;
		if (mTurnSpeed>=0.0f&&mTurnSpeed<0.5f){
			mTurnSpeed = 0.5f;
		}
		if (mTurnSpeed < 0.0f){
			mTurnSpeed += 0.11f;
			//mTurnSpeed += 0.08f;
		}
		mTurnSpeed += 0.04f;
		//mTurnSpeed += 0.02f;
	}
	else if (CKey::Push(VK_RIGHT) && CanMove){//�n���h�����E�ɁI
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
			SoundEngine.Repeat();
			isSoundEngine = true;
		}		
	}
	//�Ԃ���~���Ă��鎞
	else if (mCarSpeed == 0.0f){
		SoundEngine.Stop();
		isSoundEngine = false;
	}
	//�Ԃ��o�b�N���Ă��鎞
	else if (mCarSpeed < 0.0f){
		if (isSoundEngine == false){
			//�o�b�N�͈Ⴄ����炷�\��
			SoundEngine.Repeat();
			isSoundEngine = true;
		}
	}

	mPosition = CVector(mADMoveX, 0.0f, mWSMoveZ + mCarSpeed) * mMatrixRotate * mMatrixTranslate;
	CCharacter::Update();
	//Y����(�d��)�͕�����
	//mPosition = CVector(0.0f, mVelocityJump, 0.0f) * mMatrix;//�ł��ĂȂ�
	mPosition = CVector(0.0f, mVelocityJump*2.0f, 0.0f) * //mMatrixScale * 
		CMatrix().RotateZ(0) *
		CMatrix().RotateX(0) *
		CMatrix().RotateY(0)
		*mMatrixTranslate;

	//�]�����Ă��܂�����(R�L�[�ő����X�^�[�g)
	if (mPosition.mY < -700.0f || CKey::Once('R')){
		//�����̐�����0�ɂ���
		mVelocityJump = 0.0f;
		//�Ԃ̑��x��0��
		mCarSpeed = 0.0f;
		if (CSceneTitle::mMode == 2){
			if (mChecks == 0){
				//�X�^�[�g���̈ʒu�A�����ɖ߂����
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mStartRotation = 0.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(2893.0f, mStartPoint[1], 2473.0f);
				mStartRotation = -59.0f;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1020.0f, mStartPoint[1], 4594.0f);
				mStartRotation = -506.4f;
			}
			else if (mChecks == 3){
				mPosition = CVector(-1277.0f, mStartPoint[1], -448.0f);
				mStartRotation = -200.0f;
			}
		}
		else if (CSceneTitle::mMode == 3){
			if (mChecks == 0){
				//�X�^�[�g���̈ʒu�A�����ɖ߂����
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mStartRotation = 90.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(1127.4f, mStartPoint[1] + 100.0f, -5054.0f);
				mStartRotation = -59.0f;
			}
			else if (mChecks == 2){
				mPosition = CVector(777.0f, mStartPoint[1], 1925.0f);
				mStartRotation = 405.1f;
			}
			else if (mChecks == 3){
				mPosition = CVector(-5861.0f, mStartPoint[1], 1165.0f);
				mStartRotation = -583.5f;
			}
		}
		else if (CSceneTitle::mMode == 5){
			if (mChecks == 0){
				//�X�^�[�g���̈ʒu�A�����ɖ߂����
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mStartRotation = -145.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(-16054.4f, 4915.0f, -2180.0f);
				mStartRotation = -174.6f;
			}
			else if (mChecks == 2){
				mPosition = CVector(4680.0f, 13.5f, -2027.0f);
				mStartRotation = 147.2f;
			}
			else if (mChecks == 3){
				mPosition = CVector(14809.0f, 13.5f, 4270.0f);
				mStartRotation = -9.5f;
			}
		}
		else{
			if (mChecks == 0){
				//�X�^�[�g���̈ʒu�A�����ɖ߂����
				mPosition = CVector(mStartPoint[0], mStartPoint[1], mStartPoint[2]);
				mStartRotation = 0.0f;
			}
			else if (mChecks == 1){
				mPosition = CVector(-80.0f, mStartPoint[1], 2175.0f);
				mStartRotation = -55.0f;
			}
			else if (mChecks == 2){
				mPosition = CVector(-1620.0f, mStartPoint[1], 450.0f);
				mStartRotation = -175.0f;
			}
			else if (mChecks == 3){
				mPosition = CVector(-1212.0f, mStartPoint[1], -1616.0f);
				mStartRotation = 120.0f;
			}
		}
		mRotation = CVector(0.0f, mStartRotation, 0.0f);
		isRespawn = true;
	}

	CCharacter::Update();
	
	//�d�͂̉e���𔽉f����
	mVelocityJump -= G;
	if (mJumpPrio > 0){
		mJumpPrio--;
	}

	if (CKey::Once('L')){
		mPosition = CVector(0.0f, 100.0f, 0.0f);
		CCharacter::Update();
	}
	
}

void CPlayer::Collision(CCollider *mc, CCollider *yc){
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
									mCarSpeed = 3.2f +1.8f;
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
				if (yc->mpParent->mTag == CCharacter::EGOALPOINT){//���Ԓn�_3
					if (mChecks == 3){
						//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
						CVector aiu;//�����킹�̂��߂����̃x�N�g��
						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
							isTouchGoal = true;
						}
					}
				}
				/*else{
					isTouchGoal = false;
				}*/
				if (mCanSwim && yc->mpParent->mTag == CCharacter::EWATER){
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
					//�����͍s���邪�A�����̃p�l���͒ʉ߉\
				}
				else{
					if (mJumpPrio < 1){

						CVector adjust;//�����p�x�N�g��
						//		//�O�p�`�Ƌ��̏Փ˔���
						//		CCollider::CollisionTriangleSphere(yc, mc, &adjust);
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
									//mCarSpeed /= 2.0f;
									SoundCollision.Play();
									//���ˎ��A�G�t�F�N�g����
									new CEffect(mPosition + CVector(0.0f,35.0f,0.0f), 100.0f, 100.0f, TextureExp, 4, 4, 1, 0);
								}
								else if (mCarSpeed > 4.0f){
									mCarSpeed = 2.0f;
									SoundCollisionSmall.Play();
									//�y���Ԃ��������G�t�F�N�g����
									new CEffect(mPosition + CVector(0.0f, 15.5f, 0.0f), 60.0f, 60.0f, TextureHit, 3, 8,	1, 1);
								}
								else{
									//�ǂɂ�����Ȃ���̈ړ����A���x���x���Ȃ�
									if (mCarSpeed > 2.0f){
										mCarSpeed = 2.0f;
									}
								}								
							}
							else if(yc->mpParent->mTag == CCharacter::EJUMPER){//�W�����v��ɐڐG������
								//mVelocityJump = 0; 
								mVelocityJump = JUMPER01_POWER;
								mCanJump = true;
								SoundJump.Play();
							}
							else{
								mVelocityJump = 0;
								mCanJump = true;
								mRotation = CCollider::CalculateEulerAngle(mc, yc, mMatrixRotate, PI);
							}
						}
					}

				}
			}
			//�����̃R���C�_������̎�
			if (mc->mTag == CCollider::ESEARCH){
				//�������ɏ�������̏���
				if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
					CVector aiueo;//�Ƃ�܃x�N�g��
					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
						//mCarSpeed += 10.0f;
						//mCarSpeed = MAXSPEED+10.0f;						
						if (isBoost == false){
							SoundBoost.Play();
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
				if (yc->mpParent->mTag == CCharacter::ESPRING){
					mJumpV0 = 2.2f;
					SoundItemGet.Play();
				}
				if (yc->mpParent->mTag == CCharacter::ESCREW){
					mCanSwim = true;
					SoundItemGet.Play();
				}
				if (yc->mpParent->mTag == CCharacter::EKEY){
					mIsGetKey = true;
					SoundItemGet.Play();
				}
				if (yc->mpParent->mTag == CCharacter::EBOAT){//�{�[�g��D��
					mHaveBoat = true;
					mMoveSpeed = 0.85f;
				}


				if (mc->mTag == CCollider::EBODY){
					if (yc->mpParent->mTag == CCharacter::EENEMY){
						if (yc->mTag == CCollider::EBODY){
							CVector adjust;//�����p�x�N�g��
							////		//�����m�̏Փ˔���
							if (CCollider::Collision(mc, yc, &adjust)){
								//�ʒu�̍X�V
								mPosition = mPosition - adjust * -1;
								//�s��̍X�V
								CCharacter::Update();
								//printf("�����̏Փˏ���");
								//SoundCollisionSmall.Play();
							}
						}
					}
				}
				
			}
		}
		break;
	}
}


void CPlayer::TaskCollision()
{
	mColBody.ChangePriority();
	mColTire.ChangePriority();
	//mColCamRange.ChangePriority();
	//mColCamera.ChangePriority();
	CollisionManager.Collision(&mColBody);
	CollisionManager.Collision(&mColTire);
	//CollisionManager.Collision(&mColCamRange);	
	//CollisionManager.Collision(&mColCamera);
}