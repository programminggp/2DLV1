#include "CEnemy.h"
//�G�t�F�N�g�N���X�̃C���N���[�h
#include "CEffect.h"
//
#include "CSceneGame.h"
//
#include "CBullet.h"

//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture> TextureExp;

//�U���|�C���g
CPoint *CEnemy::mPoint;
int CEnemy::mPointSize = 0;

#define TURN_DEG 0.3f

//�R���X�g���N�^
//CEnemy(���f��, �ʒu, ��], �g�k)
CEnemy::CEnemy(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 0.8f)
//?SearchEnemy
, mSearch(this, CVector(0.0f, 0.0f, 60.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f / scale.mX, 1.0f / scale.mY, 1.0f / scale.mZ), 10.0f)
,mHp(20)
, mPointCnt(0)
{
	//
	mCollider.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	mPointCnt = 0;	//�ŏ��̃|�C���g��ݒ�
	mpPoint = &mPoint[mPointCnt];//�ڎw���|�C���g�̃|�C���^��ݒ�
	mTag = EENEMY;
}
//�X�V����
void CEnemy::Update() {
	//�|�C���g�ւ̃x�N�g�������߂�
	CVector dir = mpPoint->mPosition - mPosition;
	//�������̃x�N�g�������߂�
	CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	//������̃x�N�g�������߂�
	CVector up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
	//���E�̉�]�����iY���j
	if (left.Dot(dir) > 0.0f) {
		mRotation.mY += 0.3f;
	}
	else if (left.Dot(dir) < 0.0f) {
		mRotation.mY -= 0.3f;
	}
	//�㉺�̉�]�����iX���j
	if (up.Dot(dir) > 0.0f) {
		mRotation.mX -= 0.3f;
	}
	else if (up.Dot(dir) < 0.0f) {
		mRotation.mX += 0.3f;
	}

	//�s����X�V
	CCharacter::Update();
	//�ʒu���ړ�
	mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	//��]������
//	mRotation.mY += 0.5f;

	if (mHp < 0) {
		mHp--;
		mRotation.mX = 20;
		if (mHp % 10 == 0) {
			new CEffect(mPosition, 1.5f, 1.5f, TextureExp, 4, 4, 2);
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
						mPointCnt++;//���̃|�C���g�ɂ���
						//�Ōゾ������ŏ��ɂ���
						mPointCnt %= mPointSize;
						//���̃|�C���g�̃|�C���^��ݒ�
						mpPoint = &mPoint[mPointCnt];
					}
					break;
				case EMISSILE:
					mEnabled = false;
				default:
					if (y->mTag == CCollider::EBODY) {
						//�G�t�F�N�g����
						new CEffect(mPosition, 1.0f, 1.0f, TextureExp, 4, 4, 1);
						//			mHp--;
					}
				}
			}
			//�폜		mEnabled = false;
		}
	}
}
