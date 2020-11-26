#include "CEnemy2.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"

#define OBJ "f16.obj"
#define MTL "f16.mtl"

CModel CEnemy2::mModel;

CEnemy2::CEnemy2()
: mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
{
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	mpModel = &mModel;
}


//�R���X�g���N�^
//CEnemy(�ʒu, ��], �g�k)
CEnemy2::CEnemy2(CVector position, CVector rotation, CVector scale)
	: CEnemy2()
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�

	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //�폜����
	CTaskManager::Get()->Add(this); //�ǉ�����
}

//�X�V����
void CEnemy2::Update() {
	//�s����X�V
	CTransform::Update();
	//�ʒu���ړ�
	mPosition = CVector(0.0f, 0.0f, 0.9f) * mMatrix;
}
//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CEnemy2::Collision(CCollider *m, CCollider *o) {
	//����̃R���C�_�^�C�v�̔���
	switch (o->mType)
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă��鎞�͖����ɂ���
			//mEnabled = false;
		}
		break;
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
		}
		break;
	}
}

void CEnemy2::TaskCollision()
{
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
//	mCollider3.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
//	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);
}
