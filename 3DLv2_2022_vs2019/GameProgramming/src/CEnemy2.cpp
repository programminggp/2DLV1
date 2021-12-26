#include "CEnemy2.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CPlayer.h"

#define OBJ "res\\f16.obj"	//���f���̃t�@�C��
#define MTL "res\\f16.mtl"	//���f���̃}�e���A���t�@�C��

#define HP 3	//�ϋv�l
#define VELOCITY 0.11f	//���x

CModel CEnemy2::mModel;	//���f���f�[�^�쐬

#define FIRECOUNT 15	//���ˊԊu


CEnemy2::CEnemy2()
: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
, mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, 100.0f), 30.0f)
, mpPlayer(0)
, mHp(HP)
, mFireCount(0)
{
	mTag = EENEMY;
	mColSearch.Tag(CCollider::ESEARCH);	//�^�O�ݒ�

	//���f���������Ƃ��͓ǂݍ���
	if (mModel.Triangles().size() == 0)
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
	//�ڕW�n�_�̐ݒ�
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

//�X�V����
void CEnemy2::Update() {

	//HP��0�ȉ��̎��@���j
	if (mHp <= 0)
	{
		mHp--;
		//15�t���[�����ɃG�t�F�N�g
		if (mHp % 15 == 0)
		{
			//�G�t�F�N�g����
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		//���~������
//		mPosition.mY -= 0.03f;
		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		CTransform::Update();	//�s��X�V
		return;	//�Ăь��֖߂�
	}


	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;

	if (mFireCount > 0)
	{
		mFireCount--;
	}
	else
	{
		//�v���C���[�̃|�C���^��0�ȊO�̎�
		if (mpPlayer != nullptr)
		{
			//�v���C���[�܂ł̃x�N�g�������߂�
			CVector vp = mpPlayer->Position() - mPosition;
			float dx = vp.Dot(vx);	//���x�N�g���Ƃ̓��ς����߂�
			float dy = vp.Dot(vy);	//��x�N�g���Ƃ̓��ς����߂�
			float dz = vp.Dot(vz);

			//X���̃Y����2.0�ȉ�
			if (-2.0f < dx && dx < 2.0f)
			{
				//Y���̃Y����2.0�ȉ�
				if (-2.0f < dy && dy < 2.0f)
				{
					if (dz > 0.0f)
					{
						mFireCount = FIRECOUNT;
						//�e�𔭎˂��܂�
						CBullet *bullet = new CBullet();
						bullet->Set(0.1f, 1.5f);
						bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
						bullet->Rotation(mRotation);
						bullet->Update();
					}
				}
			}
		}
	}

	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	float dx = vp.Dot(vx);	//���x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(vy);	//��x�N�g���Ƃ̓��ς����߂�
	float margin = 0.1f;
	//���E�����։�]
	if (dx > margin)
	{
//		mRotation.mY += 1.0f;
		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f);
	}
	else if (dx < -margin)
	{
//		mRotation.mY -= 1.0f;
		mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f);
	}
	//�㉺�����։�]
	if (dy > margin)
	{
//		mRotation.mX -= 1.0f;
		mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f);
	}
	else if (dy < -margin)
	{
//		mRotation.mX += 1.0f;
		mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f);
	}

	//�ړ�����
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;

	CTransform::Update();	//�s��X�V

	//���悻3�b���ɖڕW�n�_���X�V
	int r = rand() % 180;	//rand()�͐����̗�����Ԃ�
							//% 180 ��180�Ŋ������]������߂�
	if (r == 0)
	{
		if (mpPlayer)
		{
			mPoint = mpPlayer->Position();
		}
		else
		{
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}

	mpPlayer = nullptr;

}
//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy2::Collision(CCollider *m, CCollider *o) {
	//���肪�T�[�`�̎��͖߂�
	if (o->Tag() == CCollider::ESEARCH)
	{
		return;
	}
	//�������T�[�`�p�̎�
	if (m->Tag() == CCollider::ESEARCH)
	{
		//���肪���R���C�_�̎�
		if (o->Type() == CCollider::ESPHERE)
		{
			//���肪�v���C���[�̎�
			if (o->Parent()->Tag() == EPLAYER)
			{
				//�Փ˂��Ă��鎞
				if (CCollider::Collision(m, o))
				{
					//�v���C���[�̃|�C���^�ݒ�
					mpPlayer = o->Parent();
				}
			}
		}
		return;
	}

	switch (o->Type())
	{
	case CCollider::ESPHERE:
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			mHp--;	//�q�b�g�|�C���g�̌��Z
		}
		break;
	case CCollider::ETRIANGLE:	//�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
			//���j�Œn�ʂɏՓ˂���Ɩ���
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}

	return;

	switch (m->Tag())
	{
	case CCollider::ESEARCH:
		if (o->Type() == CCollider::ESPHERE)
		{
			if (o->Parent()->Tag() == EPLAYER)
			{
				//�R���C�_��m��y���Փ˂��Ă��邩����
				if (CCollider::Collision(m, o))
				{
					//�v���C���[�̃|�C���^��ݒ�
					mpPlayer = o->Parent();
				}
			}
		}
		break;
	default:	//�{�̂̎�
		switch (o->Type())
		{
		case CCollider::ESPHERE:
			if (o->Tag() == CCollider::EBODY)
			{
				//�R���C�_��m��y���Փ˂��Ă��邩����
				if (CCollider::Collision(m, o)) {
					//�G�t�F�N�g����
					new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
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


	if (o->Tag() == CCollider::ESEARCH)
		return;
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			switch (m->Tag())
			{
			case CCollider::ESEARCH:
				if (o->Parent()->Tag() == EPLAYER)
				{
					//�v���C���[�̃|�C���^��ݒ�
					mpPlayer = o->Parent();
				}
				break;
			default:
				//�G�t�F�N�g����
				new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			}
		}
		break;
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		if (m->Tag() == CCollider::EBODY)
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