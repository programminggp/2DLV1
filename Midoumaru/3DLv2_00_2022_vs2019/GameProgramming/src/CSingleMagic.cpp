#include "CSingleMagic.h"
#include "CCollisionManager.h"
#include"CCollision.h"

#define MODEL_FireBall "res\\FireBall.obj","res\\FireBall.mtl"

CSingleMagic::CSingleMagic(const CVector& position, const CVector& rotation, const CVector& scale)
	: SMagicLife(45)
	, mCollider(this, &mMatrix, CVector(0.0f, 0.9f, 0.0f), 1.0f)
{
	if (mFireBall.Triangles().size() == 0){
		mFireBall.Load(MODEL_FireBall);
	}
	
	mpModel = &mFireBall;
	Position(position);
	Rotation(rotation);
	Scale(scale);

	mTag = ESINGLEMAGIC;
	mCollider.Tag(CCollider::EPLAYERSMAGIC);
}

//���Ɖ��s���̐ݒ�
//Set(��, ���s)
void CSingleMagic::Set(float w, float d) {
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

//�X�V
void CSingleMagic::Update() {
	CTransform::Update();
	//�������Ԃ̔���
	if (SMagicLife-- > 0) {
		CTransform::Update();
		//�ʒu�X�V
		mPosition = CVector(0.0f, 0.0f, 0.4f) * mMatrix;
	}
	else {
		//�����ɂ���
		mEnabled = false;
	}
}

//�`��
void CSingleMagic::Render() {
	CCharacter::Render();
	return;
	////DIFFUSE���F�ݒ�
	//float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	////�O�p�`�`�恨12
	//mT.Render(mMatrix);
	//mCollider.Render();
}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CSingleMagic::Collision(CCollider* m, CCollider* o) {
	CVector adjust;
	if (CCollision::CollisionAll(m, o, &adjust)) {
		if (o->Type() == CCollider::ETRIANGLE) {
			mEnabled = false;
		}
		if (o->Tag()==CCollider::ECORE){
			mEnabled = false;
		}
	}
}
void CSingleMagic::TaskCollision()
{
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}

