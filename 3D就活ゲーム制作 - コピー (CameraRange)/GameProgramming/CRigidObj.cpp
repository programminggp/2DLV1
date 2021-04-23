#include "CRigidObj.h"
#include "CTaskManager.h"

CRigidObj *CRigidObj::mpRigObj = 0;

#define G (9.8f / 120.0f)//�d�͉����x//60.0f

//CRigidObj::CRigidObj()
////:mColBody(this, CVector(0.0f, 4.0f + 1.0f, 0.5f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 10.0f)
//{
//	mpRigObj = this;
//
//	//mScale = CVector(2.5f, 2.5f, 2.5f);
//	mVelocity = 0.0f;
//	mJumpPrio = 0;
//	//CanMove = false;
//
//	//mTag = EPLAYER;
//	//CCharacter::Update();
//
//	//mColBody.mTag = CCollider::EBODY;
//
//}


//�R���X�g���N�^
//model:���f���̃|�C���^ position:�ʒu rotation:��] scale:�g�k
CRigidObj::CRigidObj(CModel *model, const CVector &position, const CVector &rotation, const CVector &scale)
:mpCollider(0)
, mColBody(this, CVector(0.0f, 0.0f - 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 21.0f)
, mColBody2nd(this, CVector(0.0f, 0.0f + 3.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 31.0f)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;

	mpRigObj = this;
	mVelocity = 0.0f;
	mJumpPrio = 0;

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

	//if (mObjNumber == 99 || mObjNumber == 575){
	//	//�����蔻��𐶐����Ȃ�
	//	//����ɂ�蓖���蔻��̐��𑝂₷�قǏ������d���Ȃ邱�Ƃ����؂��ꂽ
	//	//�t�ɓ����蔻��𑝂₳�Ȃ���΂����̂ŁA�K�v�Ȃ������蔻��͂ǂ�ǂ�J�b�g���Ă�����B
	//}
	//else{
	//	CCharacter::Update();
	//	//���f���̎O�p�`�̐����A�R���C�_�̔z����쐬���܂�
	//	mpCollider = new CCollider[model->mTriangles.size()];
	//	for (int i = 0; i < model->mTriangles.size(); i++){
	//		//�R���C�_���O�p�`�R���C�_�Őݒ肵�Ă����܂�
	//		mpCollider[i].SetTriangle(this,
	//			model->mTriangles[i].mV[0],
	//			model->mTriangles[i].mV[1],
	//			model->mTriangles[i].mV[2]);
	//		//if (mObjNumber == 111){
	//		//	//�������̓����蔻�肾����Ɉړ�������
	//		//	model->mTriangles[i].mV[0] = model->mTriangles[i].mV[0] + CVector(0.0f, 5.0f, 0.0f);
	//		//	model->mTriangles[i].mV[1] = model->mTriangles[i].mV[1] + CVector(0.0f, 5.0f, 0.0f);
	//		//	model->mTriangles[i].mV[2] = model->mTriangles[i].mV[2] + CVector(0.0f, 5.0f, 0.0f);
	//		//}
	//		mpCollider[i].ChangePriority();
	//	}
	//}


	//mVelocity = 0.0f;

	//mEnabled = false;
}
//�f�X�g���N�^
CRigidObj::~CRigidObj(){
	//�R���C�_������΍폜
	if (mpCollider){
		//delete[] �z����폜
		delete[] mpCollider;
	}
}

void CRigidObj::Update(){
	mPosition = CVector(0.0f, mVelocity*2.0f, 0.0f) * //mMatrixScale * 
		CMatrix().RotateZ(0) *
		CMatrix().RotateX(0) *
		CMatrix().RotateY(0)
		*mMatrixTranslate;
	CCharacter::Update();
	//�]�����Ă��܂�����(R�L�[�ő����X�^�[�g)
	if (mPosition.mY < -150.0f){
		//�����̐�����0�ɂ���
		mVelocity = 0.0f;
		mPosition.mY = 30.0f;
		CCharacter::Update();
	}	
	//�d�͂̉e���𔽉f����
	mVelocity -= G;

	if (mJumpPrio > 0){
		mJumpPrio--;
	}
}

void CRigidObj::Collision(CCollider *mc, CCollider *yc){
	//���g�̃R���C�_�^�C�v�̔���
	switch (mc->mType){
	case CCollider::ETRIANGLE://�O�p�R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (yc->mType == CCollider::ETRIANGLE){
			mVelocity = 0;
		}
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (yc->mType == CCollider::ETRIANGLE){
			//�������g�ƏՓ˂���̋֎~
			if (mc != yc){
				CVector aiueo;//�Ƃ�܃x�N�g��
				if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
					mVelocity = 1.0f;
				}
			}			
		}
	}


	////���g�̃R���C�_�^�C�v�̔���
	//switch (mc->mType){
	//case CCollider::ESPHERE://���R���C�_
	//	//����̃R���C�_���O�p�R���C�_�̎�
	//	if (yc->mType == CCollider::ETRIANGLE){
	//		//�����̃R���C�_���{�̂̎�
	//		if (mc->mTag == CCollider::EBODY){
	//			//�Ő��ʉߒ��̏���
	//			if (yc->mpParent->mTag == CCharacter::EGRASS){
	//				CVector aiueo;//���̃x�N�g��
	//				if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
	//					
	//				}
	//			}
	//			
	//			if (mCanSwim && yc->mpParent->mTag == CCharacter::EWATER){
	//				//�ʉ߉\�A�X�e�[�W1�̐�
	//			}
	//			else if (yc->mpParent->mTag == CCharacter::ECLEARWATER){
	//				//�ʉ߉\�A�X�e�[�W2�̐�
	//			}
	//			else if (yc->mpParent->mTag == CCharacter::ECHECKPOINT
	//				|| yc->mpParent->mTag == CCharacter::ECHECKPOINT2
	//				|| yc->mpParent->mTag == CCharacter::ECHECKPOINT3
	//				|| yc->mpParent->mTag == CCharacter::EDASHBOARD){
	//				//�����͍s���邪�A�����̃p�l���͒ʉ߉\
	//			}
	//			else{
	//				if (mJumpPrio < 1){
	//					CVector adjust;//�����p�x�N�g��
	//					//		//�O�p�`�Ƌ��̏Փ˔���
	//					//		CCollider::CollisionTriangleSphere(yc, mc, &adjust);
	//					if (CCollider::CollisionTriangleSphere(yc, mc, &adjust)){
	//						//�ʒu�̍X�V
	//						mPosition = mPosition - adjust * -1;
	//						//�s��̍X�V
	//						CCharacter::Update();
	//						if (yc->mpParent->mTag == CCharacter::EWALL){
	//							//�Փ˂����̂��ǂ������ꍇ�͕ǂɂ͈��������炸����
	//							//�ǂɂԂ���ƏՓˉ������A�Ԃ���������
	//							//�������ɏՓ˂Ō����A�x�����̏Փ˂͓��ɕω��Ȃ�
	//							if (mCarSpeed > 4.5f){
	//								mCarSpeed = 2.0f;
	//								//mCarSpeed /= 2.0f;
	//								SoundCollision.Play();
	//							}
	//							else if (mCarSpeed > 3.0f){
	//								mCarSpeed = 2.0f;
	//								SoundCollisionSmall.Play();
	//							}
	//							else{
	//								//�ǂɂ�����Ȃ���̈ړ����A���x���x���Ȃ�
	//								if (mCarSpeed > 2.0f){
	//									mCarSpeed = 2.0f;
	//								}
	//							}
	//						}
	//						else{
	//							mVelocityJump = 0;
	//							mCanJump = true;
	//							int rotateofycmx = yc->mpParent->mRotation.mX;
	//							rotateofycmx %= 360; //-360�x����360�x�܂ł̐��l�ɕϊ�
	//							//-235=125 300=-60 -180�x�������A180�x�ȏ�̊p�x��
	//							if (rotateofycmx < -180){
	//								rotateofycmx += 360;
	//							}
	//							else if (rotateofycmx >= 180){
	//								rotateofycmx -= 360;
	//							}
	//							mRotation.mX = rotateofycmx;
	//						}
	//					}
	//				}
	//			}
	//		}
	//		//�����̃R���C�_������̎�
	//		if (mc->mTag == CCollider::ESEARCH){
	//			//�������ɏ�������̏���
	//			if (yc->mpParent->mTag == CCharacter::EDASHBOARD){
	//				CVector aiueo;//�Ƃ�܃x�N�g��
	//				if (CCollider::CollisionTriangleSphere(yc, mc, &aiueo)){
	//					isBoost = true;
	//					mBoostTime = 45;
	//				}
	//			}
	//		}
	//	}
	//	if (yc->mType == CCollider::ESPHERE){
	//		if (CCollider::Collision(mc, yc)){
	//	
	//			if (mc->mTag == CCollider::EBODY){
	//				if (yc->mpParent->mTag == CCharacter::EENEMY){
	//					CVector adjust;//�����p�x�N�g��
	//					////		//�����m�̏Փ˔���
	//					if (CCollider::Collision(mc, yc, &adjust)){
	//						//�ʒu�̍X�V
	//						mPosition = mPosition - adjust * -1;
	//						//�s��̍X�V
	//						CCharacter::Update();
	//						//printf("�����̏Փˏ���");
	//						//SoundCollisionSmall.Play();
	//					}
	//				}
	//			}
	//		}
	//	}
	//	break;
	//}
}


void CRigidObj::TaskCollision()
{
	mColBody.ChangePriority();
	CollisionManager.Collision(&mColBody);
	mColBody2nd.ChangePriority();
	CollisionManager.Collision(&mColBody2nd);
}