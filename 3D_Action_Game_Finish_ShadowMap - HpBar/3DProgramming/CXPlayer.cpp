#include <Windows.h>
#include "CXPlayer.h"
#include "CBillBoard.h"
#include "CParticle.h"
#include "CKey.h"
#include "Define.h"
#include "CLight.h"

//�J�����̉�]���x
#define CAMERA_ROTATION_ADD 2
//�v���C���[�̃|�C���^
CXPlayer *CXPlayer::mpPlayer = 0;

/*
����������
*/
void CXPlayer::Init(CModelX *model) {
	//�v���C���[�̃|�C���^�ݒ�
	mpPlayer = this;
	//�e�̏���������
	CXCharacter::Init(model);
	//�R���C�_�̐���
	//��
	mColliders.push_back(new CSphereCollider(CCollider::EBODY, this, &mpCombinedMatrix[8+1], CVector3(), 0.5f));
	//��
	mColliders.push_back(new CSphereCollider(CCollider::EHEAD, this, &mpCombinedMatrix[11 + 1], CVector3(0.0f, 5.f, -3.0f), 0.5f));
	//��
	mColliders.push_back(new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[21 + 1], CVector3(-10.0f, 10.0f, 50.0f), 0.3f));
	//*3
	//�J�v�Z���R���C�_
	mColliders.push_back(new CCapsuleCollider(this, &mpCombinedMatrix[1], CVector3(0.0f, 10.0f, 0.0f), CVector3(0.0f, 160.0f, 0.0f), 0.7f));
}

void CXPlayer::Update() {
	CMatrix44 rot;
	CVector3 slide(0.25f, 0.0f, 0.0f);
	mAdjust = CVector3();
	//���[�V�����ɂ��U�蕪��
	switch (mState) {
	case EAVOIDANCER://����E
		mRotation.y += 12;
		mCameraRotation.y -= 12;
		rot.rotationY(mRotation.y + mCameraRotation.y);
		slide = slide * rot;
		//�X���C�h
		mPosition = mPosition - slide;
		if (mAnimationFrame >= mAnimationFrameSize) {
			//�ҋ@���[�V�����i0�ԁA�J��Ԃ��A60�t���[���j
			ChangeAnimation(0, true, 60);
			mAnimationFrameSize = 60;
			mState = EIDLE;
		}
		break;
	case EAVOIDANCEL://�����
		mRotation.y -= 12;
		mCameraRotation.y += 12;
		rot.rotationY(mRotation.y + mCameraRotation.y);
		slide = slide * rot;
		//�X���C�h
		mPosition = mPosition + slide;
		if (mAnimationFrame >= mAnimationFrameSize) {
			//�ҋ@���[�V�����i0�ԁA�J��Ԃ��A60�t���[���j
			ChangeAnimation(0, true, 60);
			mAnimationFrameSize = 60;
			mState = EIDLE;
		}
		break;
	case EIDLE://�ҋ@
	case EWALK://����
		//*7
		//D�L�[�������ƉE�։�]��
		if (CKey::Push('D')) {
			//�E�։�]
			mRotation.y -= PLAYER_ROTATION_ADD;
			mRotation.y = (int)mRotation.y % 360;
		}
		//A�L�[�������ƍ��։�]����
		if (CKey::Push('A')) {
			//���։�]
			mRotation.y += PLAYER_ROTATION_ADD;
			mRotation.y = (int)mRotation.y % 360;
		}
		//*13
		//AD�L�[�f����2�x�����ŉ��
		if (CKey::Twice('D')) {
			ChangeAnimation(0, false, 60);
			mAnimationFrame = 0;
			mAnimationFrameSize = 30;
			mState = EAVOIDANCER;
			break;
		}
		if (CKey::Twice('A')) {
			ChangeAnimation(0, false, 60);
			mAnimationFrame = 0;
			mAnimationFrameSize = 30;
			mState = EAVOIDANCEL;
			break;
		}

		//W�L�[�������ƁA�����A�j���[�V�����ɕς�
		//�����Ă��������0.1�����ړ�����
		if (CKey::Push('W')) {
			//�J�����̕����֌�����
			CMatrix44 rot;
			CVector3 camera = mPosition - GetCameraPosition();
			rot.rotationY(90);
			camera = camera * rot;
			rot.rotationY(mRotation.y);
			float dot = camera.dot(CVector3(0, 0, 1.0f)*rot);
			if (dot > 0) {
				mRotation.y -= 4.0f;
				mCameraRotation.y += 4.0f;
			}
			else if (dot < 0) {
				mRotation.y += 4.0f;
				mCameraRotation.y -= 4.0f;
			}
			rot.rotationY(mRotation.y);

			//*5
			//�ʒu���ړ�������
			mPosition = mPosition + CVector3(0, 0, PLAYER_VELOCITY)*rot;
			//�������[�V�����i1�ԁA�J��Ԃ��A60�t���[���j
			ChangeAnimation(1, true, 60);
			//�X�e�[�^�X�����
			mState = EWALK;
		}
		else if (CKey::Push('S')) {
			//�J�����̕����֌�����
			CMatrix44 rot;
			CVector3 camera = mPosition - GetCameraPosition();
			rot.rotationY(90);
			camera = camera * rot;
			rot.rotationY(mRotation.y);
			float dot = camera.dot(CVector3(0, 0, 1.0f)*rot);
			if (dot > 0) {
				mRotation.y -= 4.0f;
				mCameraRotation.y += 4.0f;
			}
			else if (dot < 0) {
				mRotation.y += 4.0f;
				mCameraRotation.y -= 4.0f;
			}
			rot.rotationY(mRotation.y);

			//*6
			//�ʒu���ړ�������
			mPosition = mPosition + CVector3(0, 0, -PLAYER_VELOCITY)*rot;
			//�������[�V�����i1�ԁA�J��Ԃ��A60�t���[���j
			ChangeAnimation(1, true, 60);
			//�X�e�[�^�X�����
			mState = EWALK;
		}
		else {	//�����ĂȂ����͑ҋ@
			//�ҋ@���[�V�����i0�ԁA�J��Ԃ��A60�t���[���j
			ChangeAnimation(0, true, 60);
			mState = EIDLE;
		}

		//SP�L�[�������ƍU��1
		if (CKey::Once(' ')) {
			//*8
			//�U��1���[�V�����i3�ԁA�J��Ԃ��Ȃ��A30�t���[���j�ɂ���
			ChangeAnimation(3, false, PLAYER_ATTACK_SPEED);
			mState = EATTACK;
//			CSoundManager::mSwing.Play();
		}
		break;
	case EATTACK://�U��1
		if (mAnimationFrame >= mAnimationFrameSize) {
			//�U��1�I��胂�[�V�����i4�ԁA�J��Ԃ��Ȃ��A30�t���[���j�ɂ���
			ChangeAnimation(4, false, PLAYER_ATTACK_SPEED);
			mState = EATTACKR;
		}
		break;
	case EATTACKR://�U��1�I���
		if (mAnimationFrame >= mAnimationFrameSize) {
			//�ҋ@���[�V�����i0�ԁA�J��Ԃ��A60�t���[���j�ɂ���
			ChangeAnimation(0, true, 60);
			mState = EIDLE;
			mHitFlg = true;
		}
		break;
	}
	//*4
	//J�L�[�ŃJ������]
	if (CKey::Push('J')) {
		mCameraRotation.y += CAMERA_ROTATION_ADD;
	}
	//L�L�[�ŃJ������]
	if (CKey::Push('L')) {
		mCameraRotation.y -= CAMERA_ROTATION_ADD;
	}

	Gravity(); //�d�͏���
	CXCharacter::Update();
	//Light�̈ʒu�ݒ�
//	CLight::getLight(0)->setPosition(mPosition + CVector3(LIGHT_POS), mPosition);
}

//�Փˏ���
bool CXPlayer::Collision(CCollider *m, CCollider *y) {
	//�����̃R���C�_�̎�ނ𔻒�
	switch (m->mTag) {
	case CCollider::ECOLSPHERE://���R���C�_
		//����̃R���C�_�̎�ޔ���
		switch (y->mTag) {
		case CCollider::ECOLSPHERE://���R���C�_
			//���R���C�_�Ƌ��R���C�_�̏Փ˔���
			if (CCollision::Sphere(m, &((CSphereCollider*)y)->GetWorld())) {
				//�G�̍U�����A�v���C���[�Ƀq�b�g
				if (y->mpParent->mTag == EENEMY	//
					&& y->mColParts == CCollider::ESWORD	//��
					&& y->mpParent->mState == EATTACK) {	//�U����
					if (m->mColParts == CCollider::EBODY	//��
						|| m->mColParts == CCollider::EHEAD) {//��
						if (m->mpParent->mState != EAVOIDANCEL &&
							m->mpParent->mState != EAVOIDANCER) {
							mHpBar.mValue -= ENEMY_ATTACK_POINT;
							if (mHpBar.mValue <= 0.0f) {
								ChangeAnimation(11, false, 60);	//�_�E��
								mState = EDOWN;
							}
						}
					}
				}
				//�v���C���[�̍U�����A�G�Ƀq�b�g
				if (y->mpParent->mTag == EENEMY	//
					&& m->mColParts == CCollider::ESWORD	//��
					&& m->mpParent->mState == EATTACK) {	//�U����
//					&& mHitFlg) {
					if (y->mColParts == CCollider::EBODY	//��
						|| y->mColParts == CCollider::EHEAD) {//��
						new CEffectHit2(m->mPosition, CVector3(2.5f, 2.5f, 0.0f), 6, 2);
						mHitFlg = false;
					}
				}
			}
			break;
		}
		break;
	case CCollider::ECOLCAPSULE://�J�v�Z���R���C�_
		//����̃R���C�_�̎�ޔ���
		switch (y->mTag) {
		case CCollider::ECOLTRIANGLE://�O�p�`�R���C�_
			CVector3 adjust;
			//�J�v�Z���R���C�_�ƎO�p�`�R���C�_�̏Փ˔���
			if (CCollision::CapsuleTriangle(m, y, &adjust)) {
				UpdateAdjust(adjust);
				//�n�ʂ����f
				if (y->mColParts == CCollider::EGROUND) {
					//�ڒn������d�͑��x0
					mVelocityG = 0.0f;
				}
			}
			break;
		}
		break;
	}
	return false;
}

void CXPlayer::Render() {
	CXCharacter::Render();
	//HP�Q�[�W�̐ݒ�ƕ\��
	mHpBar.SetPosition(mPosition + CVector3(0.0f, 0.7f, 0.0f));
	mHpBar.Render();
}
