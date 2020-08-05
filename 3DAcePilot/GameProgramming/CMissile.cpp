#include "CMissile.h"
//�G�t�F�N�g�N���X�̃C���N���[�h
#include "CEffect.h"
//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture> TextureExp;

#define MISSILE_VELOCITY 0.6f	//�~�T�C������
#define TURN_DEG 1.5f

//�R���X�g���N�^
//CAirBase(���f��, �ʒu, ��], �g�k)
CMissile::CMissile(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 0.1f)
, mLife(180)
, mpPoint(0)
{
	mCollider.mTag = CCollider::EBODY;
	mTag = EMISSILE;
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	CCharacter::Update();
}

//�Փˏ���
void CMissile::Collision(CCollider *m, CCollider *y) {
	//���ɋ��R���C�_�̎�
	if (m->mType == CCollider::ESPHERE
		&& y->mType == CCollider::ESPHERE) {
		if (y->mTag == CCollider::EBODY) {
			if (CCollider::Collision(m, y)) {
				if (y->mpParent->mTag != EPLAYER) {
					//�G�t�F�N�g����
					new CEffect(y->mPosition * y->mMatrix * y->mpParent->mMatrix, 5.0f, 5.0f, TextureExp, 4, 4, 1);
					mEnabled = false;
				}
			}
		}
	}
}

void CMissile::Update() {
	if (mpPoint) {
		//�|�C���g�ւ̃x�N�g�������߂�
		CVector dir = mpPoint->mPosition - mPosition;

		//�������̃x�N�g�������߂�
		CVector left = CVector(1.0f, 0.0f, 0.0f) * mMatrix - CVector() * mMatrix;
		left = left.Normalize();
		//������̃x�N�g�������߂�
		CVector up = CVector(0.0f, 1.0f, 0.0f) * mMatrix - CVector() * mMatrix;
		up = up.Normalize();
		CVector z = CVector(0.0f, 0.0f, 1.0f) * mMatrix - CVector() * mMatrix;
		z = z.Normalize();

		//���E�̉�]�����iY���j
		if (left.Dot(dir) > 0.0f) {
			mRotation.mY += TURN_DEG;
		}
		else if (left.Dot(dir) < 0.0f) {
			mRotation.mY -= TURN_DEG;
		}
		//�㉺�̉�]�����iX���j
		if (up.Dot(dir) > 0.0f) {
			if (z.Dot(dir) > 0.0) {
				mRotation.mX -= TURN_DEG;
			}
		}
		else if (up.Dot(dir) < 0.0f) {
			if (z.Dot(dir) > 0.0) {
				mRotation.mX += TURN_DEG;
			}
		}

	}

	mPosition = mPosition + CVector(0.0f, 0.0f, MISSILE_VELOCITY) * mMatrixRotate;
	CCharacter::Update();
	if (mLife-- < 0) {
		mEnabled = false;
	}
}
