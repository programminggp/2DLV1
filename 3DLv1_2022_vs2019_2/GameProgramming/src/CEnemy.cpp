#include "CEnemy.h"

//�ړ����x
#define VELOCITY CVector(0.0f, 0.0f, 0.09f)

void CEnemy::Collision(CCollider* m, CCollider* o)
{
	//�R���C�_��m��o���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o)) {
		//�Փ˂��Ă��鎞�͖����ɂ���
		mEnabled = false;
	}
}

//�R���X�g���N�^
//CEnemy(���f��, �ʒu, ��], �g�k)
CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	: mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -20.0f), 0.8f)
{

	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model;	//���f���̐ݒ�
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
}

//�X�V����
void CEnemy::Update() {
	//�s����X�V
	CTransform::Update();
	//�ʒu���ړ�
	mPosition = mPosition + VELOCITY * mMatrixRotate;
}
