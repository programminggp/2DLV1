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
//CPoint *CEnemy::mPoint;
//int CEnemy::mPointSize = 0;

#define TURN_DEG 0.4f

#define VELOCITY 4.4f

#define POINTTIME 120

//�R���X�g���N�^
//CEnemy(���f��, �ʒu, ��], �g�k)
CEnemy::CEnemy(CModel *model, CVector position, CVector rotation, CVector scale)
: mCollider(this, CVector(0.0f, 0.0f, 1.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 0.4f)
, mSearch(this, CVector(0.0f, 0.0f, 200.0f), CVector(0.0f, 0.0f, 0.0f),CVector(1.0f, 1.0f, 1.0f), 20.0f)
, mHp(20)
, mPointCnt(0)
, mpPoint(0)
, mFireBullet(0)
{
	//
	mCollider.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	mTag = EENEMY;
	mpPoint = &CPlayer::sPlayer->mPosition;

}
//�X�V����
void CEnemy::Update() {
	//�|�C���g�ւ̃x�N�g�������߂�
	CVector dir;

	if (mFireBullet > 0) {
		mFireBullet--;
	}

	if (mPointCnt > 0) {
		mPointCnt--;
	}
	else {
		if (mpPoint) {
			mPoint = *mpPoint;
		}
		else {
			mPoint = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
		}
//		mPointCnt = rand() % 120;
		mPointCnt = POINTTIME;
	}
	dir = mPoint - mPosition;

	//�������̃x�N�g�������߂�
//	CVector left = CVector(1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	CVector left = CVector(1.0f, 0.0f, 0.0f) * mMatrix - CVector() * mMatrix;
	left = left.Normalize();
	//������̃x�N�g�������߂�
//	CVector up = CVector(0.0f, 1.0f, 0.0f) * CMatrix().RotateX(mRotation.mX) * CMatrix().RotateY(mRotation.mY);
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
		//if (z.Dot(dir) > 0.0) {
		//	mRotation.mX += TURN_DEG;
		//}
		//else {
		//	mRotation.mX -= TURN_DEG;
		//}
	}
	else if (up.Dot(dir) < 0.0f) {
		if (z.Dot(dir) > 0.0) {
			mRotation.mX += TURN_DEG;
		}
		//if (z.Dot(dir) > 0.0) {
		//	mRotation.mX -= TURN_DEG;
		//}
		//else {
		//	mRotation.mX += TURN_DEG;
		//}
	}

	//�s����X�V
	CCharacter::Update();
	//�ʒu���ړ�
	mPosition = CVector(0.0f, 0.0f, VELOCITY) * mMatrix;
	//��]������
//	mRotation.mY += 0.5f;

	if (mHp < 0) {
		mHp--;
		mRotation.mX = 25;
		if (mHp % 10 == 0) {
			new CEffect(mPosition, 2.5f, 2.5f, TextureExp, 4, 4, 2);
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
							CBullet *bullet = new CBullet();
							bullet->Set(0.1f, 1.5f);
							bullet->mPosition = CVector(0.0f, 0.0f, 20.0f) * mMatrix;
							bullet->mRotation = mRotation;
							bullet->mTag = EBULLET;
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
//					mEnabled = false;
				case EBULLET:
					if (y->mTag == CCollider::EBODY) {
						//�G�t�F�N�g����
						new CEffect(mPosition, 2.0f, 2.0f, TextureExp, 4, 4, 1);
						mHp--;
					}
				}
			}
			//�폜		mEnabled = false;
		}
	}
}
