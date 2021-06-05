//25
#include "CXEnemy.h"
#define _USE_MATH_DEFINES
#include <math.h>

/*
����������
*/
void CXEnemy::Init(CModelX *model) {
	//�e�̏���������
	CXCharacter::Init(model);
	mState = EIDLE;
	//�R���C�_�̐���
	//��
	mpColSphereBody = new CSphereCollider(CCollider::EBODY, this, &mpCombinedMatrix[8+1], CVector3(), 0.5f);
	//��
	mpColSphereHead = new CSphereCollider(CCollider::EHEAD, this, &mpCombinedMatrix[11+1], CVector3(0.0f, 5.f, -3.0f), 0.5f);
	//��
	mpColSphereSword = new CSphereCollider(CCollider::ESWORD, this, &mpCombinedMatrix[21+1], CVector3(-10.0f, 10.0f, 50.0f), 0.3f);
	//30 �J�v�Z���R���C�_
	new CCapsuleCollider(this, &mpCombinedMatrix[7+1], CVector3(0.0f, -80.0f, 0.0f), CVector3(0.0f, 80.0f, 0.0f), 0.7f);
	//31 ���G
	new CSphereCollider(CCollider::ENONE, this, &mpCombinedMatrix[5+1], CVector3(0.0f, 0.0f, 700.0f), 10.0f);
}

void CXEnemy::Update() {
	mAdjust = CVector3();
//31
	switch (mAnimationIndex) {
	case 7:
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(8, false, 30);
			mState = EATTACK;
		}
		break;
	case 8:
		if (mAnimationFrame >= mAnimationFrameSize) {
			ChangeAnimation(0, true, 60);
			mHitFlg = true;
			mState = EIDLE;
		}
		break;
	case 11:
		if (mAnimationFrame >= mAnimationFrameSize) {
			mEnabled = false;
		}
		break;
	default:
		//�v���C���[�������Ă��鎞
		if (mpPlayer) {
			ChangeAnimation(1, true, 60);
			mState = EWALK;
			//��������v���C���[�ւ̃x�N�g�������߂�
			CVector3 ep = mPosition - mpPlayer->mPosition;
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
				mRotation.y--;
			}
			else if (dot < 0.0f) {
				mRotation.y++;
			}
			//�v���C���[�̃|�C���^��0�ɂ��܂��B
			mpPlayer = 0;
			//���l
			radian = 0.0f;
			//�߂��ɗ�����U��
			if (ep.length() < 2.4f) {
				ChangeAnimation(7, false, 90);
				mState = EATTACK;
			}
			//34 �v���C���[�ֈړ�
			mPosition = mPosition + CVector3(0.0f, 0.0f, 0.05f) * rot;
		}
		else {
			ChangeAnimation(0, true, 60);
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
#ifdef _DEBUG
	//25 �R���C�_�̕`��
	//27 �폜
	//mpColSphereBody->Render();
	//mpColSphereHead->Render();
	//mpColSphereSword->Render();
#endif
}
//27 �Փˏ���
bool CXEnemy::Collision(CCollider *m, CCollider *y) {
	//�����̃R���C�_�̎�ނ𔻒�
	switch (m->mTag) {
	case CCollider::ECOLSPHERE://���R���C�_
		//����̃R���C�_�̎�ޔ���
		switch (y->mTag) {
		case CCollider::ECOLSPHERE://���R���C�_
			//���R���C�_�Ƌ��R���C�_�̏Փ˔���
			if (CCollision::Sphere(m, &((CSphereCollider*)y)->GetWorld())) {
//31
				//�v���C���[�̃R���C�_�Ɠ������Ă����
				//�v���C���[�̃|�C���^�擾
				if (y->mpParent->mTag == EPLAYER) {
					mpPlayer = y->mpParent;
				}
				if (y->mpParent->mTag == EPLAYER	//�v���C���[
					&& y->mColParts == CCollider::ESWORD	//��
					&& y->mpParent->mState == EATTACK) {	//�U����
					if (m->mColParts == CCollider::EBODY	//��
						|| m->mColParts == CCollider::EHEAD) {//��
						ChangeAnimation(11, false, 30);	//�_�E��
						mState = EDOWN;
					}
				}
				if (y->mpParent->mTag == EPLAYER	//�v���C���[
					&& m->mColParts == CCollider::ESWORD	//��
					&& m->mpParent->mState == EATTACK	//�U����
					&& mHitFlg) {
					if (y->mColParts == CCollider::EBODY	//��
						|| y->mColParts == CCollider::EHEAD) {//��
						//�q�b�g�G�t�F�N�g����
						new CEffectHit3(m->mPosition, CVector3(2.5f, 2.5f, 0.0f), 5, 2);
						mHitFlg = false;
					}
				}
			}
			break;
		}
		break;
	//30
	case CCollider::ECOLCAPSULE://�J�v�Z���R���C�_
		//����̃R���C�_�̎�ޔ���
		switch (y->mTag) {
		case CCollider::ECOLTRIANGLE://�O�p�`�R���C�_
			CVector3 adjust;
			//�J�v�Z���R���C�_�ƎO�p�`�R���C�_�̏Փ˔���
			if (CCollision::CapsuleTriangle(m, y, &adjust)) {
				UpdateAdjust(adjust);
//				mPosition = mPosition + adjust;
				//30 �n�ʂ����f
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
