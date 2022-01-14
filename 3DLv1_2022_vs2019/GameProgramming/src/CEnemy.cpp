#include "CEnemy.h"
#include "CEffect.h"

//�R���X�g���N�^
//CEnemy(���f��,�ʒu,��],�g�k)
CEnemy::CEnemy(CModel* model, const CVector& position,
	const CVector& rotation, const CVector& scale)
	:mCollider1(this, &mMatrix,CVector(0.0f,5.0f,0.0f),0.8f)
	,mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
	,mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -20.0f), 0.8f)
{
	//���f��,�ʒu,��],�g�k��ݒ肷��
	mpModel = model; //�G�̃��f���ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
}

//�X�V����
void CEnemy::Update() {
	//�s����X�V
	CTransform::Update();
	//�ʒu���ړ�
	mPosition = CVector(0.0f, 0.0f, 0.9f) * mMatrix;
}
//�Փˏ���
//Collision(�R���C�_1,�R���C�_2)
void CEnemy::Collision(CCollider* m, CCollider* o) {
	//�R���C�_��m��o���Փ˂��Ă��邩�̔���
	if (CCollider::Collision(m,o)){
		//�G�t�F�N�g����
		new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		//�Փ˂��Ă��鎞�͖����ɂ���
		//�폜mEnabled = false;
	}
}