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
			//if (mObjNumber == 111){
			//	//�������̓����蔻�肾����Ɉړ�������
			//	model->mTriangles[i].mV[0] = model->mTriangles[i].mV[0] + CVector(0.0f, 5.0f, 0.0f);
			//	model->mTriangles[i].mV[1] = model->mTriangles[i].mV[1] + CVector(0.0f, 5.0f, 0.0f);
			//	model->mTriangles[i].mV[2] = model->mTriangles[i].mV[2] + CVector(0.0f, 5.0f, 0.0f);
			//}
			mpCollider[i].ChangePriority();
		}
	}

	

	//mVelocity = 0.0f;

	//mEnabled = false;
}
//�f�X�g���N�^
CObj::~CObj(){
	//�R���C�_������΍폜
	if (mpCollider){
		//delete[] �z����폜
		delete[] mpCollider;
	}
}

//void CObj::Collision(CCollider *m, CCollider *y){
//	//if (mObjNumber == 2001){
//	//	//���g�̃R���C�_�^�C�v�̔���
//	//	switch (m->mType){
//	//	case CCollider::ETRIANGLE:
//	//		//����̃R���C�_���O�p�R���C�_�̎�
//	//		if (y->mType == CCollider::ETRIANGLE){
//	//			//////�����̃R���C�_�������̎�
//	//			////if (m->mTag == CCollider::EBODY){					
//	//			////}
//	//			////�Ő��ʉߒ��̏���
//	//			//if (y->mpParent->mTag == CCharacter::EGRASS){
//	//			//	//CVector aiueo;//���̃x�N�g��
//	//			//	//if (CCollider::CollisionTriangleLine(y, m, &aiueo)){
//	//			//	//	mVelocity = 0;
//	//			//	//}
//	//			//}
//	//			//else{
//	//			//	mVelocity = 0;
//	//			//}
//	//			mVelocity = 0;
//	//		}
//	//	}
//	//}
//	//mVelocity = 0;//���s����ĂȂ�
//	//	//���g�̃R���C�_�^�C�v�̔���
//	//	switch (mc->mType){
//	//	case CCollider::ESPHERE://���R���C�_
//	//		//����̃R���C�_���O�p�R���C�_�̎�
//	//		if (yc->mType == CCollider::ETRIANGLE){
//	//			////���j�\�Ȏ��͐���(���̏�)��ʉ߂ł���
//	//			//if (yc->mTag == EWATER && mCanSwim){
//	//			//}
//	//			//else{
//	//			//}
//	//			////�`�F�b�N�|�C���g�֘A�̏���
//	//			//if (CCollider::Collision(mc, yc)){
//	//			//	if (yc->mpParent->mTag == CCharacter::ECHECKPOINT){//���Ԓn�_1
//	//			//		if (mChecks == 0){
//	//			//			//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
//	//			//			mChecks = 1;
//	//			//		}
//	//			//	}
//	//			//	if (yc->mpParent->mTag == CCharacter::ECHECKPOINT2){//���Ԓn�_2
//	//			//		if (mChecks == 1){
//	//			//			//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
//	//			//			mChecks = 2;
//	//			//		}
//	//			//	}
//	//			//	if (yc->mpParent->mTag == CCharacter::ECHECKPOINT3){//���Ԓn�_3
//	//			//		if (mChecks == 2){
//	//			//			//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
//	//			//			mChecks = 3;
//	//			//		}
//	//			//	}
//	//			//}
//	//			//�����̃R���C�_���{�̂̎�
//	//			if (mc->mTag == CCollider::EBODY){
//	//				//�Ő��ʉߒ��̏���
//	//				if (yc->mpParent->mTag == CCharacter::EGRASS){
//	//					CVector aiueo;//���̃x�N�g��
//	//					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
//	//						//�u�[�X�g���ʂ̕����D�悳���
//	//						if (isBoost == false){
//	//							//printf("speed down�c\n");
//	//							//��葬�x�܂ŃX�s�[�h�ቺ
//	//							if (mCarSpeed > 3.0f){
//	//								if (mCarSpeed > 3.3f){
//	//									mCarSpeed -= 0.3f;
//	//								}
//	//								else{
//	//									mCarSpeed = 3.0f;
//	//								}
//	//							}
//	//						}
//	//						/*if (mTurnSpeed <= 0.0f&&mTurnSpeed>-0.5f){
//	//						mTurnSpeed = -0.5f;
//	//						}
//	//						if (mTurnSpeed > 0.0f){
//	//						mTurnSpeed -= 0.11f;
//	//						}
//	//						mTurnSpeed -= 0.04f;*/
//	//					}
//	//				}
//	//				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT){//���Ԓn�_1
//	//					if (mChecks == 0){
//	//						//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
//	//						CVector aiu;//�����킹�̂��߂����̃x�N�g��
//	//						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
//	//							mChecks = 1;
//	//						}
//	//					}
//	//				}
//	//				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT2){//���Ԓn�_2
//	//					if (mChecks == 1){
//	//						//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
//	//						CVector aiu;//�����킹�̂��߂����̃x�N�g��
//	//						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
//	//							mChecks = 2;
//	//							//mChecks = 0;
//	//						}
//	//					}
//	//				}
//	//				if (yc->mpParent->mTag == CCharacter::ECHECKPOINT3){//���Ԓn�_3
//	//					if (mChecks == 2){
//	//						//�e���Ԓn�_��ʉ߂��Ȃ���1�������Ƃ݂Ȃ���Ȃ�
//	//						CVector aiu;//�����킹�̂��߂����̃x�N�g��
//	//						if (CCollider::CollisionTriangleSphere(yc, mc, &aiu)){
//	//							mChecks = 3;
//	//						}
//	//					}
//	//				}
//	//				////�������ɏ�������̏���
//	//				//if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
//	//				//	CVector aiueo;//�Ƃ�܃x�N�g��
//	//				//	if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
//	//				//		//mCarSpeed += 10.0f;
//	//				//		isBoost = true;
//	//				//		mBoostTime = 45;
//	//				//		printf("SPEED UP!\n");
//	//				//	}
//	//				//}
//	//				if (yc->mpParent->mTag == CCharacter::EWATER){
//	//					//�ʉ߉\�A�X�e�[�W1�̐�
//	//				}
//	//				else if (yc->mpParent->mTag == CCharacter::ECLEARWATER){
//	//					//�ʉ߉\�A�X�e�[�W2�̐�
//	//				}
//	//				else if (yc->mpParent->mTag == CCharacter::ECHECKPOINT
//	//					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT2
//	//					|| yc->mpParent->mTag == CCharacter::ECHECKPOINT3
//	//					|| yc->mpParent->mTag == CCharacter::EDASHBOARD){
//	//					//�����͍s���邪�A�����̃p�l���͒ʉ߉\
//	//				}
//	//				else{
//	//					CVector adjust;//�����p�x�N�g��
//	//					//		//�O�p�`�Ƌ��̏Փ˔���
//	//					//		CCollider::CollisionTriangleSphere(yc, mc, &adjust);
//	//					if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
//	//						//�ʒu�̍X�V
//	//						mPosition = mPosition - adjust * -1;
//	//						//�s��̍X�V
//	//						CCharacter::Update();
//	//						if (yc->mpParent->mTag == CCharacter::EWALL){
//	//							//�Փ˂����̂��ǂ������ꍇ�͕ǂɂ͈��������炸����
//	//							//�ǂɂԂ���ƏՓˉ������A�Ԃ���������
//	//							//�������ɏՓ˂Ō����A�x�����̏Փ˂͓��ɕω��Ȃ�
//	//							if (mCarSpeed > 4.5f){
//	//								mCarSpeed = 2.0f;
//	//								//mCarSpeed /= 2.0f;
//	//								//	SoundCollision.Play();
//	//								//���ˎ��A�G�t�F�N�g����
//	//								new CEffect(mPosition + CVector(0.0f, 35.0f, 0.0f), 50.0f, 50.0f, TextureExp, 4, 4, 1, 0);
//	//								//new CEffect(mPosition + CVector(0.0f, 390.0f/2, 0.0f), 390.0f, 390.0f, TextureExp, 4, 4, 111);
//	//								printf("��ݯ");
//	//							}
//	//							else if (mCarSpeed > 3.0f){
//	//								mCarSpeed = 2.0f;
//	//								//	SoundCollisionSmall.Play();
//	//								//�y���Ԃ��������G�t�F�N�g����
//	//								new CEffect(mPosition + CVector(0.0f, 15.5f, 0.0f), 17.0f, 17.0f, TextureHit, 3, 8, 1, 1);
//	//								printf("�޽�");
//	//							}
//	//							else{
//	//								//�ǂɂ�����Ȃ���̈ړ����A���x���x���Ȃ�
//	//								if (mCarSpeed > 2.0f){
//	//									mCarSpeed = 2.0f;
//	//									/*new CEffect(mPosition + CVector(0.0f, 20.0f, 0.0f), 68.0f + 12.0f, 17.0f + 3.0f, TextureHit, 1, 1, 1, 1);
//	//									new CEffect(mPosition + CVector(0.0f, 60.0f, 0.0f), 68.0f + 12.0f, 17.0f + 3.0f, TextureHit, 1, 1, 1, 0);*/
//	//								}
//	//							}
//	//							//mCarSpeed = -mCarSpeed * 1.0;
//	//							//mVelocityJump = 2.0f;
//	//						}
//	//						else{
//	//							mVelocityJump = 0;
//	//							mCanJump = true;
//	//							/*if (mRotation.mX < yc->mpParent->mRotation.mX){
//	//							mRotation.mX++;
//	//							}
//	//							else if (mRotation.mX > yc->mpParent->mRotation.mX){
//	//							mRotation.mX--;
//	//							}*/
//	//							int rotateofycmx = yc->mpParent->mRotation.mX;
//	//							rotateofycmx %= 360; //-360�x����360�x�܂ł̐��l�ɕϊ�
//	//							//-235=125 300=-60 -180�x�������A180�x�ȏ�̊p�x��
//	//							if (rotateofycmx < -180){
//	//								rotateofycmx += 360;
//	//							}
//	//							else if (rotateofycmx >= 180){
//	//								rotateofycmx -= 360;
//	//							}
//	//							mRotation.mX = rotateofycmx;
//	//							//if (mRotation.mX < yc->mpParent->mRotation.mX){
//	//							//	mRotation.mX = yc->mpParent->mRotation.mX;
//	//							//}
//	//							//else if (mRotation.mX > yc->mpParent->mRotation.mX){
//	//							//	mRotation.mX = yc->mpParent->mRotation.mX;
//	//							//}
//	//							//mRotation = yc->mpParent->mRotation;
//	//						}
//	//					}
//	//				}
//	//			}
//	//			//�����̃R���C�_������̎�
//	//			if (mc->mTag == CCollider::ESEARCH){
//	//				//�������ɏ�������̏���
//	//				if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
//	//					CVector aiueo;//�Ƃ�܃x�N�g��
//	//					if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
//	//						//mCarSpeed += 10.0f;
//	//						if (isBoost == false){
//	//							printf("SPEED UP!\n");
//	//							//SoundBoost.Play();
//	//						}
//	//						isBoost = true;
//	//						mBoostTime = 45;
//	//					}
//	//				}
//	//			}
//	//			/*if(yc->mpParent->mTag == CCharacter::ESPRING){
//	//			mJumpV0 = 2.3f;
//	//			}*/
//	//			/*if (CItem::mpItem->mItemNumber == 2){
//	//			mJumpV0 = 2.3f;
//	//			}*/
//	//		}
//	//		if (yc->mType == CCollider::ESPHERE){
//	//			if (CCollider::Collision(mc, yc)){
//	//				//
//	//				if (mc->mTag == CCollider::EBODY){
//	//					if (yc->mpParent->mTag == CCharacter::EPLAYER){
//	//						CVector adjust;//�����p�x�N�g��
//	//						////		//�����m�̏Փ˔���
//	//						if (CCollider::Collision(mc, yc, &adjust)){
//	//							//�ʒu�̍X�V
//	//							mPosition = mPosition - adjust * -1;
//	//							//�s��̍X�V
//	//							CCharacter::Update();
//	//							//printf("X:%f Y:%f Z:%f",mPosition.mX,mPosition.mY,mPosition.mZ);
//	//							//printf("�G�̏Փˏ���");
//	//						}
//	//					}
//	//					if (yc->mpParent->mTag == CCharacter::EENEMY
//	//						&& yc->mTag == CCollider::EBODY){
//	//						if (mc == yc){
//	//							return;
//	//						}
//	//						CVector adjust;//�����p�x�N�g��
//	//						////		//�����m�̏Փ˔���
//	//						if (CCollider::Collision(mc, yc, &adjust)){
//	//							//�ʒu�̍X�V
//	//							mPosition = mPosition - adjust * -1;
//	//							//�s��̍X�V
//	//							CCharacter::Update();
//	//							//printf("X:%f Y:%f Z:%f",mPosition.mX,mPosition.mY,mPosition.mZ);
//	//						}
//	//					}
//	//				}
//	//				if (mc->mTag == CCollider::ESEARCH){
//	//					//�|�C���^����|�C���^�Ɍ����Ĉړ�����
//	//					if (yc->mpParent->mTag == CCharacter::EPOINT){
//	//						CVector adjust;//�����p�x�N�g��
//	//						//		//�����m�̏Փ˔���
//	//						if (CCollider::Collision(mc, yc, &adjust)){
//	//							//�Փ˂����|�C���^�Ɩڎw���Ă���|�C���^��������
//	//							if (yc->mpParent == mpPoint){
//	//								//mPointCnt++;//���̃|�C���g�ɂ���
//	//								////�Ōゾ������ŏ��ɂ���
//	//								//mPointCnt %= mPointSize;
//	//								//mpPoint = &mPoint[mPointCnt];
//	//								int r = (mc->mRadius + yc->mRadius) * 0.8f;
//	//								int gap = (rand() % (r * 2) - r);
//	//								//�GAI��Lv�ɂ�蕪�U�l���ω�
//	//								if (CSceneTitle::mDifficulty == 1){
//	//									r = (mc->mRadius + yc->mRadius) * 0.8f;
//	//									gap = (rand() % (r * 2) - r);
//	//								}
//	//								else if (CSceneTitle::mDifficulty == 2){
//	//									r = (mc->mRadius + yc->mRadius) * 0.4f;
//	//									gap = (rand() % (r * 2) - r);
//	//								}
//	//								else if (CSceneTitle::mDifficulty == 3){
//	//									r = (mc->mRadius + yc->mRadius) * 0.2f;
//	//									gap = (rand() % (r * 2) - r);
//	//								}
//	//								//���̃|�C���g�̃|�C���^��ݒ�
//	//								if (mpPoint == mPoint){
//	//									mVPoint = mPoint2->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint2;
//	//								}
//	//								else if (mpPoint == mPoint2){
//	//									mVPoint = mPoint3->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint3;
//	//								}
//	//								else if (mpPoint == mPoint3){
//	//									mVPoint = mPoint4->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint4;
//	//								}
//	//								else if (mpPoint == mPoint4){
//	//									mVPoint = mPoint5->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint5;
//	//								}
//	//								else if (mpPoint == mPoint5){
//	//									mVPoint = mPoint6->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint6;
//	//								}
//	//								else if (mpPoint == mPoint6){
//	//									//��ՓxNormal�ȏ�ł͂���ɍׂ����|�C���g���ݒ肳��Ă���
//	//									if (CSceneTitle::mDifficulty == 2 || CSceneTitle::mDifficulty == 3){
//	//										mVPoint = mPoint7->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//										mpPoint = mPoint7;
//	//									}
//	//									else{
//	//										mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//										mpPoint = mPoint;
//	//									}
//	//								}
//	//								//�GAI��HARD�ȏ�ł̋���
//	//								else if (mpPoint == mPoint7){
//	//									mVPoint = mPoint8->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint8;
//	//								}
//	//								else if (mpPoint == mPoint8){
//	//									mVPoint = mPoint9->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint9;
//	//								}
//	//								else if (mpPoint == mPoint9){
//	//									mVPoint = mPoint10->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint10;
//	//								}
//	//								else if (mpPoint == mPoint10){
//	//									mVPoint = mPoint11->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint11;
//	//								}
//	//								else if (mpPoint == mPoint11){
//	//									mVPoint = mPoint12->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint12;
//	//								}
//	//								else if (mpPoint == mPoint12){
//	//									mVPoint = mPoint->mPosition + CVector(1.0f, 0.0f, 1.0f)*gap;
//	//									mpPoint = mPoint;
//	//								}
//	//								//printf("mpPoint�cX:%.1f Y:%.1f Z:%.1f\n", mpPoint->mPosition.mX, mpPoint->mPosition.mY, mpPoint->mPosition.mZ);
//	//							}
//	//						}
//	//					}
//	//					//switch (yc->mpParent->mTag){
//	//					//case EPOINT://�|�C���g�̎�
//	//					//	//�Փ˂����|�C���^�Ɩڎw���Ă���|�C���^��������
//	//					//	if (yc->mpParent == mpPoint){
//	//					//		mPointCnt++;//���̃|�C���g�ɂ���
//	//					//		//�Ōゾ������ŏ��ɂ���
//	//					//		mPointCnt %= mPointSize;
//	//					//		//���̃|�C���g�̃|�C���^��ݒ�
//	//					//		mpPoint = &mPoint[mPointCnt];
//	//					//		printf("a");
//	//					//	}
//	//					//	break;
//	//					//default:
//	//					//	;
//	//					//}
//	//				}
//	//			}
//	//		}
//	//		break;
//	//	}
//	//}
//
//	/*if (mObjNumber != 9){
//		if (CCollider::Collision(m, y)){
//			if (y->mpParent->mTag == CCharacter::EPLAYER){
//				mEnabled = false;
//			}
//		}
//	}*/
//	/*if (y->mpParent->mTag == CCharacter::EBULLET){
//		if (CCollider::Collision(m, y)){
//			if (y->mpParent->mTag == CCharacter::EBULLET){
//				mEnabled = false;
//				
//			}
//		}
//	}*/
//	/*if (CCollider::Collision(m, y)){
//		if (y->mpParent->mTag == CCharacter::EBULLET){
//			mEnabled = false;
//
//		}
//	}*/
//	//if (mObjNumber == 13){//��
//	//	if (CCollider::Collision(m, y)){
//	//		if (y->mpParent->mTag == CCharacter::EPLAYER){
//	//			mEnabled = false;
//	//		}
//	//	}
//	//}	
//}

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
		//�����蔻��͕K�v�Ȃ�
	//	mPosition.mY = CPlayer::mpPlayer->mPosition.mY;
	}

	CCharacter::Update();

	//���܂������Ȃ�
	/*if (mObjNumber == 13){
		if (mDeleteFlag){
			mEnabled = false;
		}
	}*/

	if (mObjNumber == 10){
		if (CItem::mTargetAmount <= 0){
			SetEnabled(false);
		}
	}
	if (mObjNumber == 22){
		if (CPlayer::mpPlayer->mIsGetKey){
			//�h�A���J��
			//mEnabled = false;
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


	//if (mObjNumber == 2001){	
	//	mPosition = CVector(0.0f, mVelocity * 2.0f, 0.0f) * //mMatrixScale * 
	//		CMatrix().RotateZ(0) *
	//		CMatrix().RotateX(0) *
	//		CMatrix().RotateY(0)
	//		*mMatrixTranslate;//�ł��Ă�H
	//	CCharacter::Update();
	//	//�R�[�X�A�E�g��
	//	if (mPosition.mY < -150.0f){
	//		//�����̐�����0�ɂ���
	//		mVelocity = 0.0f;
	//		mPosition.mY = 31.0f;
	//	}
	//	CCharacter::Update();
	//	//�d�͂̉e�����󂯂�
	//	mVelocity -= G;
	//}
}

//void CObjection::TaskCollision()
//{
//	/*mColBody.ChangePriority();
//	mColTire.ChangePriority();
//	CollisionManager.Collision(&mColBody);
//	CollisionManager.Collision(&mColTire);*/
//	//mpCollider.ChangePriority();
//	//CollisionManager.Collision(&mpCollider);
//}