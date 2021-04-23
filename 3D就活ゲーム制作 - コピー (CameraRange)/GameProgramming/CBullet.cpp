#include "CBullet.h"

CModel CBullet::mBullet;

//���Ɖ��s���̐ݒ�
//Set(��,���s)
void CBullet::Set(float w, float d){
	//�X�P�[���ݒ�
	mScale = CVector(5.0f, 5.0f, 5.0f);
	//�O�p�`�̒��_�ݒ�
	mT.SetVertex(CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f), CVector(w, 0.0f, 0.0f));
	//�O�p�`�̖@���ݒ�
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//�X�V

//void CBullet::Update(){
//	CCharacter::Update();
//	//�ʒu�X�V
//	mPosition = CVector(0.0f, 0.0f, 1.0f)* mMatrix;
//	//mPosition.mZ += 1.0f;
//}
void CBullet::Update(){
	//�������Ԃ̔���
	if (mLife-- > 0){
		CCharacter::Update();
		//�ʒu�X�V
	//	mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;//��ɏC���\��
		mPosition = CVector(0.0f, 0.0f, 1.0f) * CMatrix().RotateY(90) * mMatrix;
	}
	else{
		//�����ɂ���
		SetEnabled(false);
	}
}

//�`��
void CBullet::Render(){
	//DIFFUSE���F�ݒ�
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
	//mCollider.Render();
}

CBullet::CBullet()
: mLife(50), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 0.1f)
{
	mpModel = &mBullet;

	mCollider.mTag = CCollider::EBODY;
	mTag = EBULLET;
	//mCollider.mTag = CCollider::EBODY;
}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CBullet::Collision(CCollider *m, CCollider *y){
	//���ɋ��R���C�_�̎�
	if (m->mType == CCollider::ESPHERE && y->mType == CCollider::ESPHERE){
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, y)){
			//�@�̂̎�
			if (y->mTag == CCollider::EBODY){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				SetEnabled(false);
			}
		}
	}
}