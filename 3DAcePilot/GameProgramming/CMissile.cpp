#include "CMissile.h"

//�G�t�F�N�g�N���X�̃C���N���[�h
#include "CEffect.h"
//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture> TextureExp;


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
		CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
		//������̃x�N�g�������߂�
		CVector up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
		//���E�̉�]�����iY���j
		if (left.Dot(dir) > 0.0f) {
			mRotation.mY += 1.5f;
		}
		else if (left.Dot(dir) < 0.0f) {
			mRotation.mY -= 1.5f;
		}
		//�㉺�̉�]�����iX���j
		if (up.Dot(dir) > 0.0f) {
			mRotation.mX -= 1.5f;
		}
		else if (up.Dot(dir) < 0.0f) {
			mRotation.mX += 1.5f;
		}
	}
	mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
	CCharacter::Update();
	if (mLife-- < 0) {
		mEnabled = false;
	}
}
