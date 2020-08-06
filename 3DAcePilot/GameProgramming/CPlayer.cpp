//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include "CKey.h"
//�o���b�g�N���X�̃C���N���[�h
#include "CBullet.h"
//�^�X�N�}�l�[�W���̃C���N���[�h
#include "CTaskManager.h"
#include "CRes.h"
#include "CMissile.h"
#include "CBillBoard.h"
#include "CEffect.h"
#include "Define.h"

CPlayer *CPlayer::sPlayer = 0;
//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture> TextureExp;

CPlayer::CPlayer()
:mCollider(this,  CVector(0.0f, 0.0f, -5.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 0.8f)
, mFireMissile(0)
, mFireBullet(0)
, mSearch(this, CVector(0.0f, 0.0f, 400.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 40.0f)
, mpTarget(0)
, mVelocity(PLAYER_POWER_MIN)
{
	sPlayer = this;

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
	//A�L�[���͂ŉ�]
	if (CKey::Push('A')) {
		//3
		//Y���̉�]�l�𑝉�
		mRotation.mY += 1;
	}
	//D�L�[���͂ŉ�]
	if (CKey::Push('D')) {
		//3
		//Y���̉�]�l�����Z
		mRotation.mY -= 1;
	}
	//W�L�[���͂ŏ����
	if (CKey::Push('W')) {
		//3
		//X���̉�]�l�����Z
		mRotation.mX += 1;
	}
	//S�L�[���͂ŏ����
	if (CKey::Push('S')) {
		//3
		//X���̉�]�l�����Z
		mRotation.mX -= 1;
	}
	//7
	//I�L�[���͂ŏo��UP
	if (CKey::Push('I')) {
		mVelocity += POWER_UP;
		if (mVelocity > PLAYER_POWER_MAX) {
			mVelocity = PLAYER_POWER_MAX;
		}
	}
	//K�L�[���͂ŏo��DOWN
	if (CKey::Push('K')) {
		mVelocity -= POWER_UP;
		if (mVelocity < PLAYER_POWER_MIN) {
			mVelocity = PLAYER_POWER_MIN;
		}
	}

	//�U��
	//�X�y�[�X�L�[���͂Œe����
	if (mFireBullet > 0) {
		mFireBullet--;
	}
	else {
		//8
		//�X�y�[�X�L�[���͂Œe����
		if (CKey::Push(VK_SPACE)) {
			new CBullet(CVector(0.0f, 0.0f, 20.0f) * mMatrix, mRotation);
			mFireBullet = PLAYER_BULLET_INTERVAL;
		}
	}
	//M�L�[�Ń~�T�C������
	if (mFireMissile > 0) {
		mFireMissile--;
	}
	else {
		//9
		//M�L�[���͂Ń~�T�C������
		if (CKey::Push('M')) {
			new CMissile(&CRes::sMissileM, CVector(6.0f, -2.0f, 0.0f) * mMatrix, mRotation, CVector(0.2f, 0.2f, 0.2f));
			mFireMissile = PLAYER_MISSILE_INTERVAL;
		}
	}

	//CCharacter�̍X�V
	CCharacter::Update();
	//4
	//�ړ�������
	mPosition = mPosition + CVector(0.0f, 0.0f, mVelocity) * mMatrixRotate;
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
				case CCollider::EBODY:
					if (y->mpParent->mTag == EBULLET) {
						//�G�̒e�ɓ���������
						//�G�t�F�N�g����
						new CEffect(mPosition, 1.0f, 1.0f, TextureExp, 4, 4, 1);
						CVector v =  y->mpParent->mPosition - mPosition;
						v = v.Normalize();
						mPosition = mPosition + v;
						CCharacter::Update();
					}
					break;
				case CCollider::ESEARCH:
					return;
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
