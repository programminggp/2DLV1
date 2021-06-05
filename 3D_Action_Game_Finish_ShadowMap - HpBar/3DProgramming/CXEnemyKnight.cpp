#include "CXEnemyKnight.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Define.h"

/*
����������
*/
void CXEnemyKnight::Init(CModelX *model) {
	//�e�̏���������
	CXCharacter::Init(model);
	//�R���C�_�̐���
	//��
	mColliders.push_back(new CSphereCollider(CCollider::EBODY, this, &mpCombinedMatrix[1], CVector3(0.5f, -1.0f, 0.0f), 1.0f));
	//��
	mColliders.push_back(new CSphereCollider(CCollider::EHEAD, this, &mpCombinedMatrix[1], CVector3(0.0f, 1.f, 0.0f), 1.5f));
	//��
	mColliders.push_back(new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[26], CVector3(0.7f, 3.5f, -0.2f), 0.5f));
	//��
	mColliders.push_back(new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[26], CVector3(0.5f, 2.5f, -0.2f), 0.5f));
	//��
	mColliders.push_back(new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[26], CVector3(0.3f, 1.5f, -0.2f), 0.5f));
	//�J�v�Z���R���C�_
	mColliders.push_back(new CCapsuleCollider(this, &mpCombinedMatrix[0], CVector3(0.0f, 0.0f, 0.0f), CVector3(0.0f, 4.5f, 0.0f), 1.7f));

	//*10
	//���G
	mColliders.push_back(new CSphereCollider(CCollider::ENONE, this, &mpCombinedMatrix[1], CVector3(0.0f, 0.0f, 1.0f), 20.0f));

	//�ҋ@��Ԃɂ���
	ChangeAnimation(2, true, 200);
	mState = EIDLE;
	mScale = CVector3(ENEMYKNIGHT_SCALE, ENEMYKNIGHT_SCALE, ENEMYKNIGHT_SCALE);
}

void CXEnemyKnight::Render() {
	CXCharacter::Render();
//	mHpBar.SetPosition(mPosition + CVector3(0.0f, 4.5f, -1.0f));
	mHpBar.SetPosition(mPosition + CVector3(0.0f, 4.5f, 0.0f));
	mHpBar.Render();
}

void CXEnemyKnight::Update() {
	mAdjust = CVector3();
	switch (mState) {
	case EATTACK:
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(8, false, ENEMY_ATTACK_SPEED);
			mHitFlg = true;
			mState = EATTACKR;
		}
		break;
	case EATTACKR:
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(2, true, 200);
			mHitFlg = true;
			mState = EIDLE;
		}
		break;
	case EWALK:
	case EIDLE:
		//�v���C���[�������Ă��鎞
		if (mpPlayer) {
			if (mpPlayer->mState == EDOWN) {
				ChangeAnimation(2, true, 200);
				mState = EIDLE;
				break;
			}
			if (mState == EIDLE) {
				ChangeAnimation(1, true, 60);
				mState = EWALK;
			}
			//��������v���C���[�ւ̃x�N�g�������߂�
			CVector3 ep = mpPlayer->mPosition - mPosition;
			//��]�s���錾���܂�
			CMatrix44 rot;
			//������Y���̉�]�s������߂�
			rot.rotationY(mRotation.y);
			//X����������1�̃x�N�g�����쐬����
			CVector3 vx(1.0f, 0.0f, 0.0f);
			//�쐬�����x�N�g����������Y����]������]������
			vx = vx * rot;
			//��]�������x�N�g���ƃv���C���[�ւ̃x�N�g���̓��ς����߂�
			float dot = ep.dot(vx);
			//���ς̒l�ɂ����Y���̉�]�l�𑝌�����
			if (dot > 0.0f) {
				mRotation.y -= 2;
			}
			else if (dot < 0.0f) {
				mRotation.y += 2;
			}
			//�v���C���[�̃|�C���^��0�ɂ��܂��B
			mpPlayer = 0;
			//���l
			radian = 0.0f;
			//�߂��ɗ�����U��
			if (ep.length() < ENEMY_ATTACK_RANGE) {
				//*11
				//�U���A�j���[�V����
				ChangeAnimation(7, false, ENEMY_ATTACK_SPEED);
				//�X�e�[�^�X���U����
				mState = EATTACK;
			}
			else {
				//�v���C���[�ֈړ�
				mPosition = mPosition + CVector3(0.0f, 0.0f, -ENEMY_VELOCITY) * rot;
			}
		}
		else {
			ChangeAnimation(2, true, 200);
			mState = EIDLE;
			//���
			//���W�A���ɉ��Z
			radian += 0.02f;
			//2�΂𒴂�����
			if (radian > M_PI*2) {
				//2�Ό��Z
				radian -= M_PI*2;
			}
			//sin�֐������p
			mRotation.y += sinf(radian) * 2;
		}
		break;
	}
	Gravity(); //�d�͏���
	CXCharacter::Update();
}
//�Փˏ���
bool CXEnemyKnight::Collision(CCollider *m, CCollider *y) {
	//�����̃R���C�_�̎�ނ𔻒�
	switch (m->mTag) {
	case CCollider::ECOLSPHERE://���R���C�_
		//����̃R���C�_�̎�ޔ���
		switch (y->mTag) {
		case CCollider::ECOLSPHERE://���R���C�_
			//���R���C�_�Ƌ��R���C�_�̏Փ˔���
			if (CCollision::Sphere(m, &((CSphereCollider*)y)->GetWorld())) {
				//�v���C���[�̃R���C�_�Ɠ������Ă����
				//�v���C���[�̃|�C���^�擾
				if (y->mpParent->mTag == EPLAYER) {
					mpPlayer = y->mpParent;
				}
				//�v���C���[�̍U�����A�����ɓ����������H
				if (y->mpParent->mTag == EPLAYER	//�v���C���[
					&& y->mColParts == CCollider::ESWORD	//��
					&& y->mpParent->mAnimationIndex == 3
					/*&& y->mpParent->mHitFlg*/) {	//�U����
					if (m->mColParts == CCollider::EBODY	//��
						|| m->mColParts == CCollider::EHEAD) {//��
						mHpBar.mValue -= PLAYER_ATTACK_POINT;
						if (mHpBar.mValue <= 0.0f) {
							ChangeAnimation(11, false, 60);	//�_�E��
							mState = EDOWN;
						}
					}
				}
				//�����̍U�����A�v���C���[�ɓ����������H
				if (y->mpParent->mTag == EPLAYER	//�v���C���[
					&& m->mColParts == CCollider::ESWORD	//��
					&& m->mpParent->mState == EATTACK	//�U����
					&& mHitFlg) {
					if (y->mpParent->mState != EAVOIDANCEL &&
						y->mpParent->mState != EAVOIDANCER) {
						if (y->mColParts == CCollider::EBODY	//��
							|| y->mColParts == CCollider::EHEAD) {//��
							//�q�b�g�G�t�F�N�g����
							new CEffectHit3(m->mPosition, CVector3(2.5f, 2.5f, 0.0f), 5, 2);
							mHitFlg = false;
						}
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
