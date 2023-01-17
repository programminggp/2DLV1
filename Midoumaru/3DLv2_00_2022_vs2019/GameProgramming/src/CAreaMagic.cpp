#include "CAreaMagic.h"
#include "CCollisionManager.h"
#include"CCollision.h"

CAreaMagic::CAreaMagic(const CVector& position, const CVector& rotation, const CVector& scale)
	: AMagicLife(40)
	, mCollider(this, &mMatrix, CVector(0.0f, 2.0f, 0.0f), 0.8f)
{
	Position(position);
	Rotation(rotation);
	Scale(scale);
	//	Set(scale.X(), scale.Y());
	mTag = EAREAMAGIC;
	mCollider.Tag(CCollider::EPLAYERAMAGIC);
}

//���Ɖ��s���̐ݒ�
//Set(��, ���s)
void CAreaMagic::Set(float w, float d) {
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ聨3
	mT.Vertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//�O�p�`�̖@���ݒ�
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//�X�V
void CAreaMagic::Update() {
	//�������Ԃ̔���
	if (AMagicLife-- > 0) {
		CTransform::Update();
		//�ʒu�X�V
		mPosition = CVector(0.0f, 0.0f, 0.3f) * mMatrix;
	}
	else {
		//�����ɂ���
		mEnabled = false;
	}
}

//�`��
void CAreaMagic::Render() {
	//DIFFUSE���F�ݒ�
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`�恨12
	mT.Render(mMatrix);
	mCollider.Render();
}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CAreaMagic::Collision(CCollider* m, CCollider* o) {
	CVector adjust;
	if (CCollision::CollisionAll(m, o, &adjust)) {
		if (o->Type() == CCollider::ETRIANGLE) {
			mEnabled = false;
		}
		if (o->Tag() == CCollider::ECORE) {
			mEnabled = false;
		}
	}
}
void CAreaMagic::TaskCollision()
{
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}