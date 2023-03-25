#include "CBullet.h"
#include "CCollisionManager.h"

void CBullet::Collision()
{
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CBullet::Collision(CCollider* m, CCollider* o) {
	//�R���C�_��m��o���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o)) {
		//�Փ˂��Ă��鎞�͖����ɂ���
		mEnabled = false;
	}
}

CBullet::CBullet()
	: mLife(50)
	, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.1f)
{
}


//���Ɖ��s���̐ݒ�
//Set(��, ���s)
void CBullet::Set(float w, float d) {
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ聨�q���g 3
	mT.Vertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//�O�p�`�̖@���ݒ�
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//�X�V
void CBullet::Update() {
	//�������Ԃ̔���
	if (mLife-- > 0) {
		CTransform::Update();
		//�ʒu�X�V
		mPosition = mPosition + CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	}
	else {
		//�����ɂ���
		mEnabled = false;
	}
}

//�`��
void CBullet::Render() {
	//DIFFUSE���F�ݒ�
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`�恨�q���g 12
	mT.Render(mMatrix);
//	mCollider.Render();
}
