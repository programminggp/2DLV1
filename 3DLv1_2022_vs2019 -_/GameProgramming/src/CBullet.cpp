#include "CBullet.h"
#include"CApplication.h"

void CBullet::Collision()
{
	mCollider.ChangePriority();
	CCollisionManager::Instance()->Collision(&mCollider, 30);
}

//�Փˏ���
//Collision(�R���C�_�P�A �R���C�_�Q)
void CBullet::Collision(CCollider* m, CCollider* o)
{
	//�R���C�_��m��o���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o)) {
		//�Փ˂��Ă��鎞�͖����ɂ���
		mEnabled = false;
	}
}

CBullet::CBullet()
	:mLife(50)
	,mCollider(this,&mMatrix,CVector(0.0f,0.0f,0.0f),0.1f)
{}

//���Ɖ��s�̐ݒ�
//Set(���A���s)
void CBullet::Set(float w, float d) {
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ�
	mT.Vertex(CVector(-w, 0.0f, 0.0f), CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d));
	//�O�p�`�̖@���ݒ�
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//�X�V
void CBullet::Update(){
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

void CBullet::Render() {
	/*mCollider.Render();*/
	//DIFFUSE���F�ݒ�
	float c[] = { 1.0f,1.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
}