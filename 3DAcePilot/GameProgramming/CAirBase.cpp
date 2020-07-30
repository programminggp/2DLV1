#include "CAirBase.h"

//�G�t�F�N�g�N���X�̃C���N���[�h
#include "CEffect.h"
//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture> TextureExp;


//�R���X�g���N�^
//CAirBase(���f��, �ʒu, ��], �g�k)
CAirBase::CAirBase(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(350.0f, 1.0f, -1800.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 5.0f)
, mDamage(0)
{
	mCollider.mTag = CCollider::EBODY;
	mTag = EAIRBASE;
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
}

//�Փˏ���
void CAirBase::Collision(CCollider *m, CCollider *y) {
	//���ɋ��R���C�_�̎�
	if (m->mType == CCollider::ESPHERE
		&& y->mType == CCollider::ESPHERE) {
		if (y->mTag == CCollider::EBODY) {
			if (CCollider::Collision(m, y)) {
				mDamage++;
				//�G�t�F�N�g����
				new CEffect(y->mPosition * y->mMatrix * y->mpParent->mMatrix, 5.0f, 5.0f, TextureExp, 4, 4, 1);
			}
		}
	}
}
