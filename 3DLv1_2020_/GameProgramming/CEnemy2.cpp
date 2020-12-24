#include "CEnemy2.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CPlayer.h"

#define OBJ "f16.obj"	//���f���̃t�@�C��
#define MTL "f16.mtl"	//���f���̃}�e���A���t�@�C��

CModel CEnemy2::mModel;	//���f���f�[�^�쐬

CEnemy2::CEnemy2()
: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
, mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, 100.0f), 30.4f)
, mpPlayer(0)
{
	mTag = EENEMY;
	mColSearch.mTag = CCollider::ESEARCH;	//�^�O�ݒ�

	//���f���������Ƃ��͓ǂݍ���
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
}


//�R���X�g���N�^
//CEnemy(�ʒu, ��], �g�k)
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale)
	: CEnemy2()
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V
	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //�폜����
	CTaskManager::Get()->Add(this); //�ǉ�����
}

//�X�V����
void CEnemy2::Update() {
	//�v���C���[�̃|�C���^��0�ȊO�̎�
	if (mpPlayer)
	{
		//�e�𔭎˂��܂�
		CBullet *bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
		bullet->mRotation = mRotation;
		bullet->Update();
	}

	mpPlayer = 0;

	return;

	//�^�[�Q�b�g������Ƃ�
	if (mpPlayer)
	{
		CVector dir = mpPlayer->mPosition - mPosition;
		CVector left = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
		CVector top = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
		CVector front = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
		float dx = dir.Dot(left);
		float dy = dir.Dot(top);
		float dz = dir.Dot(front);

		if (abs(dx) < 2.0f)
		{
			if (abs(dy) < 2.0f)
			{
				if (abs(dz) < 50.0f && dz > 0.0f)
				{
					CBullet *bullet = new CBullet();
					bullet->Set(0.1f, 1.5f);
					bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
					bullet->mRotation = mRotation;
					bullet->Update();
				}
			}
		}
		/*
		if (left.Dot(dir) > 0.0f)
		{
			mRotation.mY += 0.75f;
		}
		else
		{
			mRotation.mY -= 0.75f;
		}
		if (top.Dot(dir) > 0.0f)
		{
			mRotation.mX -= 0.75f;
		}
		else
		{
			mRotation.mX += 0.75f;
		}
		*/
	}
	//�s����X�V
	CTransform::Update();
	return;

	//�s����X�V
	CTransform::Update();
	//�ʒu���ړ�
	mPosition = CVector(0.0f, 0.0f, 0.95f) * mMatrix;
	//
//	CVector dir = *mpTarget - mPosition;
	CVector dir =  mPosition;
	CVector left = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	CVector top = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	if (left.Dot(dir) > 0.0f)
	{
		mRotation.mY += 0.75f;
	}
	else
	{
		mRotation.mY -= 0.75f;
	}
	if (top.Dot(dir) > 0.0f)
	{
		mRotation.mX -= 0.75f;
	}
	else
	{
		mRotation.mX += 0.75f;
	}

}
//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy2::Collision(CCollider *m, CCollider *o) {
	//���肪�T�[�`�̎��͖߂�
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//�������T�[�`�p�̎�
	if (m->mTag == CCollider::ESEARCH)
	{
		//���肪���R���C�_�̎�
		if (o->mType == CCollider::ESPHERE)
		{
			//���肪�v���C���[�̎�
			if (o->mpParent->mTag == EPLAYER)
			{
				//�Փ˂��Ă��鎞
				if (CCollider::Collision(m, o))
				{
					//�v���C���[�̃|�C���^�ݒ�
					mpPlayer = o->mpParent;
				}
			}
		}
		return;
	}

	switch (o->mType)
	{
	case CCollider::ESPHERE:
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		break;
	case CCollider::ETRIANGLE:	//�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
		}
		break;
	}

	return;

	switch (m->mTag)
	{
	case CCollider::ESEARCH:
		if (o->mType == CCollider::ESPHERE)
		{
			if (o->mpParent->mTag == EPLAYER)
			{
				//�R���C�_��m��y���Փ˂��Ă��邩����
				if (CCollider::Collision(m, o))
				{
					//�v���C���[�̃|�C���^��ݒ�
					mpPlayer = o->mpParent;
				}
			}
		}
		break;
	default:	//�{�̂̎�
		switch (o->mType)
		{
		case CCollider::ESPHERE:
			if (o->mTag == CCollider::EBODY)
			{
				//�R���C�_��m��y���Փ˂��Ă��邩����
				if (CCollider::Collision(m, o)) {
					//�G�t�F�N�g����
					new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
				}
			}
			break;
		case CCollider::ETRIANGLE:	//�O�p�R���C�_�̎�
			CVector adjust; //�����l
			//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
				mPosition = mPosition + adjust;
			}
			break;
		}
	}

	return;


	if (o->mTag == CCollider::ESEARCH)
		return;
	//����̃R���C�_�^�C�v�̔���
	switch (o->mType)
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			switch (m->mTag)
			{
			case CCollider::ESEARCH:
				if (o->mpParent->mTag == EPLAYER)
				{
					//�v���C���[�̃|�C���^��ݒ�
					mpPlayer = o->mpParent;
				}
				break;
			default:
				//�G�t�F�N�g����
				new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			}
		}
		break;
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		if (m->mTag == CCollider::EBODY)
		{
			CVector adjust; //�����l
			//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
				mPosition = mPosition + adjust;
			}
		}
		break;
	}
}

void CEnemy2::TaskCollision()
{
	mCollider.ChangePriority();
	mColSearch.ChangePriority();
//	mCollider3.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSearch, COLLISIONRANGE);
//	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);
}
