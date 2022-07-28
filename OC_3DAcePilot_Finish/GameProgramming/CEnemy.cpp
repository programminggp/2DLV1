#include "CEnemy.h"
#include "CEffect.h"
#include "CPlayer.h"
#include "CBullet.h"

#include "Define.h"

//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture> TextureExp;

//�R���X�g���N�^
//CEnemy(���f��, �ʒu, ��], �g�k)
CEnemy::CEnemy(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 0.4f)
, mSearch(this, CVector(0.0f, 0.0f, 200.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 20.0f)
, mHp(2)
, mPointCnt(0)
, mpTarget(0)
, mFireBullet(0)
, mVelocity(ENEMY_POWER_MAX)
{
	mCollider.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	mTag = EENEMY;
	mpTarget = &CPlayer::sPlayer->mPosition;
	mPoint = *mpTarget;
}
//�X�V����
void CEnemy::Update() {
	//�|�C���g�ւ̃x�N�g�������߂�
	CVector dir;

	dir = mPoint - mPosition;

	if (mFireBullet > 0) {
		mFireBullet--;
	}

	if (mPointCnt > 0) {
		mPointCnt--;
	}
	else {
		if (dir.Length() < 550.0f) {
//		if (mpTarget) {
			mPoint = *mpTarget;
		}
		else {
			//mPoint = mPosition + CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
			mPoint = mPoint* CMatrix().RotateY(45);
		}
		mPointCnt = ENEMY_POINTCOUNT;
	}

	mVelocity = dir.Length() / 10.0f;
	if (mVelocity > ENEMY_POWER_MAX) {
		mVelocity = ENEMY_POWER_MAX;
	}
	else if (mVelocity < ENEMY_POWER_MIN) {
		mVelocity = ENEMY_POWER_MIN;
	}

	//�������̃x�N�g�������߂�
	CVector left = CVector(1.0f, 0.0f, 0.0f) * mMatrix - CVector() * mMatrix;
	left = left.Normalize();
	//������̃x�N�g�������߂�
	CVector up = CVector(0.0f, 1.0f, 0.0f) * mMatrix - CVector() * mMatrix;
	up = up.Normalize();
	CVector z = CVector(0.0f, 0.0f, 1.0f) * mMatrix - CVector() * mMatrix;
	z = z.Normalize();

	//���E�̉�]�����iY���j
	if (left.Dot(dir) > 0.1f) {
		mRotation.mY += ENEMY_TURN_DEG;
	}
	else if (left.Dot(dir) < 0.1f) {
		mRotation.mY -= ENEMY_TURN_DEG;
	}
	//�㉺�̉�]�����iX���j
	if (up.Dot(dir) > 0.1f) {
		if (z.Dot(dir) > 0.0) {
			if (mRotation.mX > -60.0f)
			{
				mRotation.mX -= ENEMY_TURN_DEG;
			}
		}
		else {
			mRotation.mX = 0.0f;
		}
	}
	else if (up.Dot(dir) < 0.1f) {
		if (z.Dot(dir) > 0.0) {
			if (mRotation.mX < 60.0f)
			{
				mRotation.mX += ENEMY_TURN_DEG;
			}
		}
		else {
			mRotation.mX = 0.0f;
		}
	}

	//�s����X�V
	CCharacter::Update();
	//�ʒu���ړ�
	mPosition = mPosition + CVector(0.0f, 0.0f, mVelocity) * mMatrixRotate;

	if (mHp < 0) {
		mHp--;
		mRotation.mX = 55;
		if (mHp % 10 == 0) {
			new CEffect(mPosition, 2.5f, 2.5f, TextureExp, 4, 4, 2);
		}
		if (mHp < -500) {
			mEnabled = false;
		}
	}
}

void CEnemy::Collision(CCollider *m, CCollider *y) {
	//���ɋ��R���C�_�̎�
	if (m->mType == CCollider::ESPHERE
		&& y->mType == CCollider::ESPHERE) {
		if (CCollider::Collision(m, y)) {
			//�R���C�_���T�[�`������
			if (m->mTag == CCollider::ESEARCH) {
				//�Փ˂����R���C�_�̐e�̎�ނ𔻒�
				switch (y->mpParent->mTag) {
				case EAIRBASE://��R��n
				case EPLAYER://�v���C���[�̎�
					if (y->mTag == CCollider::EBODY) 
					{
						if (mFireBullet == 0)
						{
							new CBullet(CVector(0.0f, 0.0f, 20.0f) * mMatrix, mRotation);
							mFireBullet = 15;
						}
					}
					break;
				}
			}
			else  {
				//�Փ˂����R���C�_�̐e�̎�ނ𔻒�
				switch (y->mpParent->mTag) {
				case EMISSILE:
					mHp -= 10;
				case EBULLET:
					if (y->mTag == CCollider::EBODY) {
						//�G�t�F�N�g����
						new CEffect(mPosition, 2.0f, 2.0f, TextureExp, 4, 4, 1);
						mHp--;
					}
				}
			}
		}
	}
}