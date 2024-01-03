#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"
#include "CColliderManager.h"

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius)
	: CCollider()
{
	//�e�ݒ�
	mpParent = parent;
	//�e�s��ݒ�
	mpMatrix = matrix;
	//CTransform�ݒ�
	mPosition = position; //�ʒu
	//���a�ݒ�
	mRadius = radius;
	//�R���W�����}�l�[�W�����ɒǉ�
//	CCollisionManager::Instance()->Add(this);
	ChangePriority();
}

void CCollider::ChangePriority()
{
	CColliderManager::Instance()->Remove(this);
	//�����̍��Wx�e�̕ύX�s��������ă��[���h���W�����߂�
	mCenter = mPosition * *mpMatrix;
	CColliderManager::Instance()->Add(this);
}

void CCollider::ChangePriority(int priority)
{
	mPriority = priority;
	CCollisionManager::Instance()->Remove(this); //�@��U���U
	CCollisionManager::Instance()->Add(this); //�ǉ�
}

//CollisionTriangleSphere(�O�p�R���C�_�A���R���C�_�A�����l)
//return:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
// �����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
bool CCollider::CollisionTriangleSphere(CCollider* t, CCollider* s, CVector* a)
{
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	//�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//���R���C�_�����[���h���W�ō쐬
	sv = s-> mPosition** s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	CColliderLine line(nullptr, nullptr, sv, ev);
	//�O�p�R���C�_�Ɛ��R���C�_�̏Փˏ���
	return CollisionTriangleLine(t, &line, a);
}

bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a){
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	sv = l->mV[0] * *l->mpMatrix;
	ev = l->mV[1] * *l->mpMatrix;
	//�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//�O�p�̒��_��������n�_�ւ̃x�N�g�������߂�
	CVector v0sv = sv - v[0];
	//�O�p�̒��_��������I�_�ւ̃x�N�g�������߂�
	CVector v0ev = ev - v[0];
	//�������ʂƁ@�������Ă��邩���ςŊm�F����
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//�v���X�͌������Ă��Ȃ�
	if (dots * dote >= 0.0f) {
		//�Փ˂��ĂȂ�(�����s�v)
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����͖ʂƌ������Ă���
	
	//�ʂƐ����̌�_�����߂�
	// ��_�̌v�Z
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dots)));

	//��_���O�p�`���Ȃ�Փ˂��Ă���
	// ���_1���_�Q�x�N�g���ƒ��_��_�x�N�g���Ƃ̊O�ς����߁A
	// �@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//�Փ˂��Ă��Ȃ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//���_�Q���_�R�x�N�g���g���_�Q��_�x�N�g���Ƃ̊O�ς����߁A
	// �@�H��Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		//�Փ˂��Ă��Ȃ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	// ���_�R���_�P�x�N�g�����_�R��_�x�N�g���Ƃ̊O�ς����߁A
	// �@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		//�Փ˂��Ă��Ȃ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//�����l�v�Z(�Փ˂��Ȃ��ʒu�܂Ŗ߂�)
	if (dots < 0.0f) {
		//�n�_������
		*a = normal * -dots;
	}
	else {
		//�I�_������
		*a = normal * -dote;
	}
	return true;
}

bool CCollider::CollisionTriangleBotan(CCollider* t, CCollider* b, CVector* a)
{
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	//�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//���R���C�_�����[���h���W�ō쐬
	sv = b->mPosition * *b->mpMatrix + normal * b->mRadius;
	ev = b->mPosition * *b->mpMatrix - normal * b->mRadius;
	CColliderLine botan(nullptr, nullptr, sv, ev);
	//�O�p�R���C�_�Ɛ��R���C�_�̏Փˏ���
	return CollisionTriangleLine(t, &botan, a);
}

CCollider::EType CCollider::Type()
{
	return mType;
}

CCollider::CCollider()
	: mpParent(nullptr)
	, mpMatrix(&mMatrix)
	, mType(ESPHERE)
	, mRadius(0)
{
	//�R���C�_�^�X�N�z��̏�����
	for (int i = 0; i < COLLIDERTASK_SIZE; i++)
	{
		mpColliderTask[i] = nullptr;
	}
	//�R���C�_�}�l�[�W���ɒǉ�
	CColliderManager::Instance()->Add(this);
}

//�Փ˔���
	//Collision(�R���C�_�P�A�R���C�_�Q)
	//return:ture(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
bool CCollider::Collision(CCollider* m, CCollider* o) {
	//�e�R���C�_�̒��S���W�����߂�
	//���_�~�R���C�_�̕ϊ��s��~�e�̕ϊ��s��
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	//���S���璆�S�ւ̃x�N�g�������߂�
	mpos = mpos - opos;
	//���S�̋��������a�̍��v��菬�����ƏՓ�
	if (m ->mRadius + o->mRadius > mpos.Length()) {
		//�Փ˂��Ă���
		return true;
	}
	//�Փ˂��Ă��Ȃ�
	return false;
}

CCollider::~CCollider() {
	//�R���C�_�}�l�[�W������폜
	CColliderManager::Instance()->Remove(this);
//	CColliderManager::Instance()->Delete(this);
}

CCharacter3* CCollider::Parent()
{
	return mpParent;
}

void CCollider::Render() {
	glPushMatrix();
	//�R���C�_�̒��S���W���v�Z
	//�����̍��W���e�̕ϊ��s����|����
	CVector pos = mPosition * *mpMatrix;
	//���S���W�ֈړ�
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//���̕`��
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}