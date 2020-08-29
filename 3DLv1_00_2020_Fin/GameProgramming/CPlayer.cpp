//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include "CKey.h"
//�o���b�g�N���X�̃C���N���[�h
#include "CBullet.h"
//22extern CBullet Bullet;
//�^�X�N�}�l�[�W���̃C���N���[�h
#include "CTaskManager.h"
//?
#include "CMissile.h"
#include "CRes.h"
//?
#include "CBillBoard.h"

CPlayer::CPlayer()
:mCollider(this,  CVector(0.0f, 0.0f, -5.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(5.0f, 5.0f, 5.0f), 0.8f)
, mFire(0)
, mSearch(this, CVector(0.0f, 0.0f, 80.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(5.0f, 5.0f, 5.0f), 80.0f)
, mpTarget(0)
{
	mTag = EPLAYER;//��ނ̓v���C���[
	mCollider.mTag = CCollider::EBODY;//��ނ͋@��
	mSearch.mTag = CCollider::ESEARCH;

	//�����R���C�_�̐ݒ�
	//�O��
	mLine[0].SetLine(this, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f));
	//�㉺
	mLine[1].SetLine(this, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f));
	//��
	mLine[2].SetLine(this, CVector(0.0f, 0.0f, -8.0f), CVector(9.0f, 0.0f, -8.0f));
	//�E
	mLine[3].SetLine(this, CVector(0.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f));
}

//�X�V����
void CPlayer::Update() {
	if (mFire > 0) {
		mFire--;
	}
	//A�L�[���͂ŉ�]
	if (CKey::Push('A')) {
		//Y���̉�]�l�𑝉�
		mRotation.mY += 1;
	}
	//I�L�[���͂őO�i
	if (CKey::Push('U')) {
		//Z��������1�i�񂾒l����]�ړ�������
		mPosition = CVector(0.0f, 0.0f, 5.0f) * mMatrix;
	}
	//I�L�[���͂őO�i
	if (CKey::Push('I')) {
		//Z��������1�i�񂾒l����]�ړ�������
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	//D�L�[���͂ŉ�]
	if (CKey::Push('D')) {
		//Y���̉�]�l�����Z
		mRotation.mY -= 1;
	}
	//S�L�[���͂ŏ����
	if (CKey::Push('S')) {
		//X���̉�]�l�����Z
		mRotation.mX -= 1;
	}
	//W�L�[���͂ŏ����
	if (CKey::Push('W')) {
		//X���̉�]�l�����Z
		mRotation.mX += 1;
	}
	//�X�y�[�X�L�[���͂Œe����
	if (CKey::Push(VK_SPACE)) {
		CBullet *bullet = new CBullet();
		bullet->Set(0.05f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
 		bullet->mRotation = mRotation;
//		TaskManager.Add(bullet);
	}
	//�X�y�[�X�L�[���͂Œe����
	if (CKey::Push('M') && mFire == 0) {
		mFire = 60;
		if (mpTarget) {
			CMissile *m = new CMissile(&CRes::mMissileM, CVector(6.0f, -2.0f, 0.0f) * mMatrix, mRotation, CVector(0.2f, 0.2f, 0.2f));
			m->mpPoint = mpTarget;
		}
		else {
			new CMissile(&CRes::mMissileM, CVector(6.0f, -2.0f, 0.0f) * mMatrix, mRotation, CVector(0.2f, 0.2f, 0.2f));
		}
		//		TaskManager.Add(bullet);
	}
	//CCharacter�̍X�V
	CCharacter::Update();
	mpTarget = 0;

}

//�Փˏ���
void CPlayer::Collision(CCollider *m, CCollider *y) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType) {
	case CCollider::ELINE://�����R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (y->mType == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			CCollider::CollisionTriangleLine(y, m, &adjust);
			//�ʒu�̍X�V
			mPosition = mPosition - adjust * -1;
			//�s��̍X�V
			CCharacter::Update();
		}
		break;
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_�����R���C�_�̎�
		if (y->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, y)) {
				switch (m->mTag) {
				case CCollider::ESEARCH:
					if (y->mpParent->mTag == EENEMY) {
						CBillBoard b(y->mpParent->mPosition,1.0f, 1.0f);
						if (mpTarget == 0) {
							mpTarget = y->mpParent;
							b.mMaterial.mDiffuse[0] = 1.0f;
							b.mMaterial.mDiffuse[1] = 0.0f;
							b.mMaterial.mDiffuse[2] = 0.0f;
							b.mMaterial.mDiffuse[3] = 0.5f;
							b.Update();
							b.Render();
						}
						else if (mpTarget == y->mpParent) {
							b.mMaterial.mDiffuse[0] = 1.0f;
							b.mMaterial.mDiffuse[1] = 0.0f;
							b.mMaterial.mDiffuse[2] = 0.0f;
							b.mMaterial.mDiffuse[3] = 0.5f;
							b.Update();
							b.Render();
						}
						else {
							b.mMaterial.mDiffuse[0] = 0.0f;
							b.mMaterial.mDiffuse[1] = 1.0f;
							b.mMaterial.mDiffuse[2] = 0.0f;
							b.mMaterial.mDiffuse[3] = 0.5f;
							b.Update();
							b.Render();
						}
					}
					break;
				}
			}
		}
		break;
	}
}
