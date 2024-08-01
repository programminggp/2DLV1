#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"

void CCollider::ChangePriority(int priority)
{
	mPriority = priority;
	CCollisionManager::Instance()->Remove(this); //��U�폜
	CCollisionManager::Instance()->Add(this); //�ǉ�
}

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
	sv = s->mPosition * *s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	CColliderLine line(nullptr, nullptr, sv, ev);
	//�O�p�R���C�_�Ɛ��R���C�_�̏Փˏ���
	return CollisionTriangleLine(t, &line, a);
}

CCollider::CCollider()
	: mpParent(nullptr)
	, mpMatrix(&mMatrix)
	, mType(EType::ESPHERE)
	, mRadius(0)
{
	//�R���W�����}�l�[�W���ɒǉ�
	CCollisionManager::Instance()->Add(this);
}

//�Փ˔���
//Collision(�R���C�_1, �R���C�_2)
//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
bool CCollider::Collision(CCollider* m, CCollider* o) {
	//�e�R���C�_�̒��S���W�����߂�
	//���_�~�R���C�_�̕ϊ��s��~�e�̕ϊ��s��
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	//���S���璆�S�ւ̃x�N�g�������߂�
	mpos = mpos - opos;
	//���S�̋��������a�̍��v��菬�����ƏՓ�
	if (m->mRadius + o->mRadius > mpos.Length()) {
		//�Փ˂��Ă���
		return  true;
	}
	//�Փ˂��Ă��Ȃ�
	return false;
}

CCollider::~CCollider() {
	//�R���W�������X�g����폜
	CCollisionManager::Instance()->Remove(this);
}

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius, ETag tag)
	: CCollider() 
{
	mTag = tag;//�^�O�̐ݒ�
	//�e�ݒ�
	mpParent = parent;
	//�e�s��ݒ�
	mpMatrix = matrix;
	//CTransform�ݒ�
	mPosition = position; //�ʒu
	//���a�ݒ�
	mRadius = radius;
	//�R���W�����}�l�[�W��y�ɒǉ�
	//CCollisionManager::Instance()->Add(this);
}

CCharacter3* CCollider::Parent()
{
	return mpParent;
}

void CCollider::Render() {
	glPushMatrix();
	//�R���C�_�̒��S���W���v�Z
	//�����̍��W�~�e�̕ϊ��s����|����
	CVector pos = mPosition * *mpMatrix;
	//���S���W�ֈړ�
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//���`��
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}

CCollider::EType CCollider::Type()
{
	return mType;
}

bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a) {
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
	//�������ʂƌ������Ă��邩���ςŊm�F����
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//�v���X�͌������ĂȂ�
	if (dots * dote >= 0.0f) {
		//�Փ˂��ĂȂ��i�����s�v�j
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����͖ʂƌ������Ă���
	//�ʂƐ����̌�_�����߂�
	//��_�̌v�Z
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dote)));

	//��_���O�p�`���Ȃ�Փ˂��Ă���
	//���_1���_2�x�N�g���ƒ��_1��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//���_2���_3�x�N�g���ƒ��_2��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//�ۑ�R�Q
	//���_3���_1�x�N�g���ƒ��_3��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����l�v�Z�i�Փ˂��Ȃ��ʒu�܂Ŗ߂��j
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

//�D��x�̕ύX
void CCollider::ChangePriority()
{
	//�����̍��W�~�e�̕ϊ��s����|���ă��[���h���W�����߂�
	CVector pos = mPosition * *mpMatrix;
	//�x�N�g���̒������D��x
	ChangePriority(pos.Length());
	//mPriority = pos.Length();
	//CCollisionManager::Instance()->Remove(this); //��U�폜
	//CCollisionManager::Instance()->Add(this); //�ǉ�
}

CCollider::ETag CCollider::Tag()
{
	return mTag;
}

void CCollider::Matrix(CMatrix* m)
{
	mpMatrix = m;
}


//CalcCalcPointLineDist(�_, �n�_, �I�_, ����̍ŒZ�_, ����)
//�_�Ɛ��i�n�_�A�I�_��ʂ钼���j�̍ŒZ���������߂�
float CalcPointLineDist(const CVector& p, const CVector& s, const CVector& e, CVector* mp, float* t)
{
	*t = 0.0f; //�����̏�����
	CVector v = e - s; //�n�_����I�_�ւ̃x�N�g�������߂�
	float dvv = v.Dot(v); //�x�N�g���̒�����2������߂�
	if (dvv > 0.0f) {
		*t = v.Dot(p - s) / dvv; //����̐����ƂȂ�_�̊��������߂�
		// ��̎��̐���
		// dot(v, p-sp) �� |v||p-sp|cos��
		// dvv��|v|�̂Q��
		// ��̌v�Z�ŁAt�� |p-sp|cos�� / |v|�ƂȂ�B
		// �܂�t�́udot�œ��e����������v�̒����v�Ƃ��������ɂȂ�
	}
	*mp = s + v * *t; //����̐����ƂȂ�_�����߂�
	return (p - *mp).Length(); //�����̒�����Ԃ�
}


//CalcLineLineDist(�n�_1, �I�_1, �n�_2, �I�_2, ��_1, ��_2, �䗦1, �䗦2)
//2���Ԃ̍ŒZ������Ԃ�
float CalcLineLineDist(
	const CVector& s1, //�n�_1
	const CVector& e1, //�I�_1
	const CVector& s2, //�n�_2
	const CVector& e2, //�I�_2
	CVector* mp1, //��_1
	CVector* mp2, //��_2
	float* t1, //�䗦1
	float* t2  //�䗦2
)
{
	CVector v1 = e1 - s1;
	CVector v2 = e2 - s2;
	//2���������s
	if (v1.Cross(v2).Length() < 0.000001f) {
		//����1�̎n�_���璼��2�܂ł̍ŒZ�������ɋA������
		*t1 = 0.0f;
		*mp1 = s1;
		float dist = CalcPointLineDist(*mp1, s2, e2, mp2, t2);
		return dist;
	}
	//2���������s�łȂ�
	float dv1v2 = v1.Dot(v2);
	float dv1v1 = v1.Dot(v1);
	float dv2v2 = v2.Dot(v2);
	CVector vs2s1 = s1 - s2;
	//�䗦1�����߂�
	*t1 = (dv1v2 * v2.Dot(vs2s1) - dv2v2 * v1.Dot(vs2s1))
		/ (dv1v1 * dv2v2 - dv1v2 * dv1v2);
	//��_1�����߂�
	*mp1 = s1 + v1 * *t1;
	//�䗦2�����߂�
	*t2 = v2.Dot(*mp1 - s2) / dv2v2;
	//��_2�����߂�
	*mp2 = s2 + v2 * *t2;
	//�ŒZ������Ԃ�
	return (*mp2 - *mp1).Length();
}


//0�`1�̊ԂɃN�����v(�l�������I�ɂ���͈͓��ɂ��邱��)
void clamp0to1(float& v) {
	if (v < 0.0f)  v = 0.0f;
	else if (v > 1.0f)  v = 1.0f;
}
//2�����Ԃ̍ŒZ����
float CalcSegmentSegmentDist
(
	const CVector& s1, const CVector& e1, //����1
	const CVector& s2, const CVector& e2, //����2
	CVector* mp1, //�ŒZ���̒[�_1(�n�_��I�_�ɂȂ邱�Ƃ�����)
	CVector* mp2 //�ŒZ���̒[�_2(�n�_��I�_�ɂȂ邱�Ƃ�����)
)
{
	float dist = 0, t1, t2;
	//----------------------------------------------------------------
	//�Ƃ肠����2�����Ԃ̍ŒZ����,mp1,mp2,t1,t2�����߂Ă݂�
	dist = CalcLineLineDist(s1, e1, s2, e2, mp1, mp2, &t1, &t2);
	if (0.0f <= t1 && t1 <= 1.0f &&
		0.0f <= t2 && t2 <= 1.0f) {
		//mp1,mp2�������Ƃ��������ɂ�����
		return dist;
	}
	//mp1,mp2�̗����A�܂��͂ǂ��炩���������ɂȂ������̂Ŏ���
		//mp1,t1�����ߒ��� �� 
	//t2��0�`1�ɃN�����v����mp2����s1.v�ɐ������~�낵�Ă݂�
	clamp0to1(t2);
	*mp2 = s2 + (e2 - s2) * t2;
	dist = CalcPointLineDist(*mp2, s1, e1, mp1, &t1);
	if (0.0f <= t1 && t1 <= 1.0f) {
		//mp1���������ɂ�����
		return dist;
	}
	//mp1���������ɂȂ������̂Ŏ���

	//mp2,t2�����ߒ��� �� 
	//t1��0�`1�ɃN�����v����mp1����s2.v�ɐ������~�낵�Ă݂�
	clamp0to1(t1);
	*mp1 = s1 + (e1 - s1) * t1;
	dist = CalcPointLineDist(*mp1, s2, e2, mp2, &t2);
	if (0.0f <= t2 && t2 <= 1.0f) {
		//mp2���������ɂ�����
		return dist;
	}
	//mp2���������ɂȂ������̂Ŏ���

	//t2���N�����v����mp2���Čv�Z����ƁAmp1����mp2�܂ł��ŒZ
	clamp0to1(t2);
	*mp2 = s2 + (e2 - s2) * t2;
	return (*mp2 - *mp1).Length();
}

bool CCollider::CollisionCapsuleCapsule(CCollider* m, CCollider* o, CVector* adjust)
{
	CVector mp1, mp2;
	float radius = m->mRadius + o->mRadius;

	*adjust = CVector();
	if (CalcSegmentSegmentDist(m->V(0), m->V(1), o->V(0), o->V(1), &mp1, &mp2) < radius)
	{
		*adjust = mp1 - mp2;
		float len = radius - adjust->Length();
		*adjust = adjust->Normalize() * len;
		return true;
	}
	return false;
}
