#include "CC5.h"
//�G�t�F�N�g�N���X�̃C���N���[�h
#include "CEffect.h"
//
#include "CSceneGame.h"
//
#include "CBullet.h"

//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture> TextureExp;

#define TURN_DEG 0.2f

CC5::CC5(CModel *model, CVector position, CVector rotation, CVector scale)
:mCollider(this, CVector(0.0f, 5.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 1.8f)
, mCollider2(this, CVector(0.0f, 5.0f, 25.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 1.8f)
, mCollider3(this, CVector(0.0f, 5.0f, -25.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 1.8f)
, mSearch(this, CVector(0.0f, 0.0f, 60.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 0.0f)
, mHp(20)
, mpPoint(0)
{
	mCollider.mTag = CCollider::EBODY;
	mCollider2.mTag = CCollider::EBODY;
	mCollider3.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	mTag = EENEMY;
}

//�X�V����
void CC5::Update() {
	//�|�C���g�ւ̃x�N�g�������߂�
	CVector dir;

	if (mpPoint) {
		dir = mpPoint->mPosition - mPosition;
	}
	else {
		dir = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	}
	//�������̃x�N�g�������߂�
	CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	//������̃x�N�g�������߂�
	CVector up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
	//���E�̉�]�����iY���j
	if (left.Dot(dir) > 0.0f) {
		mRotation.mY += TURN_DEG;
	}
	else if (left.Dot(dir) < 0.0f) {
		mRotation.mY -= TURN_DEG;
	}
	//�㉺�̉�]�����iX���j
	if (up.Dot(dir) > 0.0f) {
		mRotation.mX -= TURN_DEG;
	}
	else if (up.Dot(dir) < 0.0f) {
		mRotation.mX += TURN_DEG;
	}

	//�s����X�V
	CCharacter::Update();
	//�ʒu���ړ�
	mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	//��]������
	//	mRotation.mY += 0.5f;

	if (mHp < 0) {
		mHp--;
		mRotation.mX = 30;
		if (mHp % 10 == 0) {
			new CEffect(mPosition, 2.5f, 2.5f, TextureExp, 4, 4, 2);
		}
	}
}

void CC5::Collision(CCollider *m, CCollider *y) {
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
					if (y->mTag == CCollider::EBODY) {
						CBullet *bullet = new CBullet();
						bullet->Set(0.1f, 1.5f);
						bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
						bullet->mRotation = mRotation;
					}
					break;
				}
			}
			else  {
				//�Փ˂����R���C�_�̐e�̎�ނ𔻒�
				switch (y->mpParent->mTag) {
				case EPOINT://�|�C���g�̎�
					//�Փ˂����|�C���^�Ɩڎw���Ă���|�C���^��������
					if (y->mpParent == mpPoint) {
					}
					break;
				case EMISSILE:
					mHp -= 10;
				case EBULLET:
					if (y->mTag == CCollider::EBODY) {
						//�G�t�F�N�g����
						new CEffect(y->mpParent->mPosition, 2.0f, 2.0f, TextureExp, 4, 4, 1);
						mHp--;
					}
					break;
				default:
					;
				}
			}
		}
	}
}
