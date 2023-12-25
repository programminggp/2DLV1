#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CCollisionManager2.h"

CCharacter* CCollider::Parent()
{
	return mpParent;
}

CCollider::CCollider()
: mpParent(nullptr)
, mpMatrix(&mMatrix)
, mType(ESPHERE)
, mTag(EBODY)
, mRadius(0)
{
	for (int i = 0; i < 9; i++)
	{
		mpColliderTask[i] = nullptr;
	}
	//�R���W�����}�l�[�W���ɒǉ�
//	CCollisionManager::Get()->Add(this);
	CCollisionManager2::Instance()->Add(this);
}

//CCollider::CCollider(bool flgAdd)
//	: mpParent(nullptr)
//	, mpMatrix(&mMatrix)
//	, mType(ESPHERE)
//	, mTag(EBODY)
//	, mRadius(0)
//{
//	for (int i = 0; i < 9; i++)
//	{
//		mpColliderTask[i] = nullptr;
//	}
//	//�R���W�����}�l�[�W���ɒǉ�
//	//CCollisionManager::Get()->Add(this);
//	//CCollisionManager2::Instance()->TM(this)->Add(this);
//	if(flgAdd)
//		CCollisionManager2::Instance()->Add(this);
//}


//�R���X�g���N�^
//CCollider(�e, �ʒu, ��], �g�k, ���a)
CCollider::CCollider(CCharacter *parent, CMatrix *matrix,
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
	Update();
}

void WireSphere(float r, int slices, int stacks)
{
	if (slices <= 0 || stacks <= 0) return;
	//Slices
	for (float thl = 0.0f; thl < M_PI * 2; thl += M_PI / slices)
	{
		glBegin(GL_LINE_STRIP);
		for (float tht = 0.0f; tht < M_PI; tht += M_PI / stacks)
		{
			glVertex3f(r*sinf(tht)*sinf(thl), r*cosf(tht), r*sinf(tht)*cosf(thl));
		}
		glEnd();
	}
}

//�`��
void CCollider::Render() {
	glPushMatrix();
	//�R���C�_�̒��S���W���v�Z
	//�����̍��W�~�e�̕ϊ��s����|����
	CVector pos = mV[0];
	//���S���W�ֈړ�
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//���C�g�I�t
	glDisable(GL_LIGHTING);
	glColor4fv(c);

	//���`��
	//glutWireSphere(mRadius, 16, 16);
	WireSphere(mRadius, 16, 16);
	//glutSolidSphere(mRadius, 16, 16);

		//���C�g�I��
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

CCollider::~CCollider()
{
//	CCollisionManager::Get()->Remove(this);
	CCollisionManager2::Instance()->Delete(this);
}
//�Փ˔���
//Collision(�R���C�_1, �R���C�_2)
//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
bool CCollider::Collision(CCollider *m, CCollider *o) {
	//�e�R���C�_�̒��S���W�����߂�
	//���_�~�R���C�_�̕ϊ��s��~�e�̕ϊ��s��
//	CVector mpos = m->mPosition * *m->mpMatrix;
//	CVector opos = o->mPosition * *o->mpMatrix;
	CVector mpos = m->mV[0];
	CVector opos = o->mV[0];
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

bool CCollider::CollisionTriangleLine(CCollider *t, CCollider *l, CVector *a) {
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	//v[0] = t->mV[0] * *t->mpMatrix;
	//v[1] = t->mV[1] * *t->mpMatrix;
	//v[2] = t->mV[2] * *t->mpMatrix;
	//sv = l->mV[0] * *l->mpMatrix;
	//ev = l->mV[1] * *l->mpMatrix;
	v[0] = t->mV[0];
	v[1] = t->mV[1];
	v[2] = t->mV[2];
	sv = l->mV[0];
	ev = l->mV[1];
	//�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	//CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	CVector normal = t->mV[3];
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
//		*a = normal * -dots;
		*a = cross - sv;
	}
	else {
		//�I�_������
//		*a = normal * -dote;
		*a = cross - ev;
	}
	return true;
}
//CollisionTriangleSphere(�O�p�R���C�_, ���R���C�_, �����l)
//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
bool CCollider::CollisionTriangleSphere(CCollider *t, CCollider *s, CVector *a)
{
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	//v[0] = t->mV[0] * *t->mpMatrix;
	//v[1] = t->mV[1] * *t->mpMatrix;
	//v[2] = t->mV[2] * *t->mpMatrix;
	v[0] = t->mV[0];
	v[1] = t->mV[1];
	v[2] = t->mV[2];
	//�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	//CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	CVector normal = t->mV[3];
	//���R���C�_�����[���h���W�ō쐬
	//sv = s->mPosition * *s->mpMatrix + normal * s->mRadius;
	//ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	sv = s->mV[0] + normal * s->mRadius;
	ev = s->mV[0] - normal * s->mRadius;

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

bool CCollider::CollisionCapsule(CCollider* m, CCollider* o, CVector* adjust)
{
	CVector mV0 = m->mV[0] * *m->mpMatrix;
	CVector mV1 = m->mV[1] * *m->mpMatrix;
	CVector oV0 = o->mV[0] * *o->mpMatrix;
	CVector oV1 = o->mV[1] * *o->mpMatrix;
	CVector r1 = (mV1 - mV0).Normalize() * m->mRadius;
	CVector r2 = (oV1 - oV0).Normalize() * o->mRadius;
	*adjust = VectorLineMinDist(mV0 + r1, mV1 - r1, oV0 + r2, oV1 - r2);
	if (adjust->Length() == 0.0f)
		return true;
	if (adjust->Length() < m->mRadius + o->mRadius)
	{
		*adjust = adjust->Normalize() * (m->mRadius + o->mRadius) - *adjust ;
		return true;
	}
	return false;
}

bool NearZero(float f)
{
	if (fabs(f) <= 0.001f)
		return true;
	return false;
}

CVector CCollider::VectorLineMinDist(const CVector& Start1, const CVector& End1, const CVector& Start2, const CVector& End2)
{
	CVector   u = End1 - Start1;
	CVector   v = End2 - Start2;
	CVector   w = Start1 - Start2;
	float    a = u.Dot(u);         // always >= 0
	float    b = u.Dot(v);
	float    c = v.Dot(v);         // always >= 0
	float    d = u.Dot(w);
	float    e = v.Dot(w);
	float    D = a * c - b * b;        // always >= 0
	float    sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
	float    tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

								   // compute the line parameters of the two closest points
	if (NearZero(D)) { // the lines are almost parallel
		sN = 0.0;         // force using point P0 on segment S1
		sD = 1.0;         // to prevent possible division by 0.0 later
		tN = e;
		tD = c;
	}
	else {                 // get the closest points on the infinite lines
		sN = (b * e - c * d);
		tN = (a * e - b * d);
		if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
			sN = 0.0;
		else if (-d > a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
			sN = 0;
		else if ((-d + b) > a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (NearZero(sN) ? 0.0f : sN / sD);
	tc = (NearZero(tN) ? 0.0f : tN / tD);

	// get the difference of the two closest points
	CVector dP = w + (u * sc) - (v * tc);  // =  S1(sc) - S2(tc)

	return dP;   // return the closest distance 

}

//�D��x�̕ύX
void CCollider::ChangePriority()
{
//	CCollisionManager2::Instance()->Remove(this);
	CCollisionManager2::Instance()->Delete(this);
	//�����̍��W�~�e�̕ϊ��s����|����
	//CVector pos = mPosition * *mpMatrix;
	//�x�N�g���̒������D��x
	mCenter = mV[0];
	mPriority = mV[0].Length();
	//CCollisionManager::Get()->Remove(this); //��U�폜
	//CCollisionManager::Get()->Add(this); //�ǉ�
	CCollisionManager2::Instance()->Add(this);
}

CCollider::EType CCollider::Type()
{
	return mType;
}

CCollider::ETag CCollider::Tag()
{
	return mTag;
}

void CCollider::Tag(ETag tag)
{
	mTag = tag;
}

void CCollider::Matrix(CMatrix* p)
{
	mpMatrix = p;
}

void CCollider::Update()
{
	mV[0] = mPosition * *mpMatrix;
	ChangePriority();
}

CColliderTask::CColliderTask(CCollider* col)
	: mpCollider(col)
{
}

CCollider* CColliderTask::Collider()
{
	return mpCollider;
}

void CColliderTask::Collider(CCollider* col)
{
	mpCollider = col;
}

CColliderTask::~CColliderTask()
{
	CCollisionManager2::Instance()->Remove(this);
}