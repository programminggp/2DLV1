#include "CCollider.h"
//�R���W�����}�l�[�W���̃C���N���[�h
#include "CCollisionManager.h"

//�R���X�g���N�^
//CCollider(�e, �ʒu, ��], �g�k, ���a)
CCollider::CCollider(CCharacter *parent, CVector position, CVector rotation, CVector scale, float radius)
: CCollider()
{
	//�e�ݒ�
	mpParent = parent;
	//CTransform�ݒ�
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	CTransform::Update();//�s��X�V
	//���a�ݒ�
	mRadius = radius;
	//�R���W�������X�g�ɒǉ�
	CollisionManager.Add(this);
	ChangePriority();
}

CCollider::~CCollider() {
	//�R���W�������X�g����폜
	CollisionManager.Remove(this);
}

//�`��
void CCollider::Render() {

	CMatrix m;

	glPushMatrix();
	glMultMatrixf((mMatrix * mpParent->mMatrix).mM[0]);

	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//���C�g�I�t
	glDisable(GL_LIGHTING);

	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f, 0.0f, 0.0f, 0.5f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//?
	//�R���C�_�^�C�v�̔���
	switch (mType) {
	case ESPHERE:
		m.Scale(1 / mpParent->mScale.mX, 1 / mpParent->mScale.mY, 1 / mpParent->mScale.mZ);
		glMultMatrixf(m.mM[0]);
		//���`��
		glutWireSphere(mRadius, 16, 16);
		break;
	case ETRIANGLE:
		m.Scale(1.01f, 1.01f, 1.01f);
		glMultMatrixf(m.mM[0]);
		//�O�p�`�`��
		glBegin(GL_TRIANGLES);
		glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
		glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
		glVertex3f(mV[2].mX, mV[2].mY, mV[2].mZ);
		glEnd();
		break;
	case ELINE:
		m.Scale(1.01f, 1.01f, 1.01f);
		glMultMatrixf(m.mM[0]);
		//�����`��
		glBegin(GL_LINES);
		glVertex3f(mV[0].mX, mV[0].mY, mV[0].mZ);
		glVertex3f(mV[1].mX, mV[1].mY, mV[1].mZ);
		glEnd();
		break;
	}

	//���C�g�I��
	glEnable(GL_LIGHTING);
	//�A���t�@�u�����h����
	glDisable(GL_ALPHA);

	glPopMatrix();
}

//�Փ˔���
//Collision(�R���C�_1, �R���C�_2)
//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
bool CCollider::Collision(CCollider *m, CCollider *y) {
	//�e�R���C�_�̒��S���W�����߂�
	//���_�~�R���C�_�̕ϊ��s��~�e�̕ϊ��s��
	CVector mpos = CVector() * m->mMatrix * m->mpParent->mMatrix;
	CVector ypos = CVector() * y->mMatrix * y->mpParent->mMatrix;
	//���S���璆�S�ւ̃x�N�g�������߂�
	mpos = mpos - ypos;
	//���S�̋��������a�̍��v��菬�����ƏՓ�
	if (m->mRadius + y->mRadius > mpos.Length()) {
		//�Փ˂��Ă���
		return  true;
	}
	//�Փ˂��Ă��Ȃ�
	return false;
}

//?
CCollider::CCollider()
: mpParent(0)
, mType(ESPHERE)
, mTag(ENONE)
{

}

//�R���X�g���N�^�i�O�p�R���C�_�j
//CCollider(�e, ���_1, ���_2, ���_3)
CCollider::CCollider(CCharacter *parent, const CVector &v0, const CVector &v1, const CVector &v2)
: CCollider()
{
	//
	SetTriangle(parent, v0, v1, v2);
}

void CCollider::SetTriangle(CCharacter *parent, const CVector &v0, const CVector &v1, const CVector &v2) {
	mType = ETRIANGLE;
	mpParent = parent;//�e�ݒ�
	//�O�p�`���_�ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
	//�X�P�[��1�{
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();//�s��X�V
	//�R���W�������X�g�ɒǉ�
	CollisionManager.Add(this);
	ChangePriority();
}

//�R���X�g���N�^�i�����R���C�_�j
//CCollider(�e, ���_1, ���_2)
CCollider::CCollider(CCharacter *parent, const CVector &v0, const CVector &v1) {
	SetLine(parent, v0, v1);
}

//�����R���C�_�̐ݒ�
//SetLine(�e, ���_1, ���_2)
void CCollider::SetLine(CCharacter *parent, const CVector &v0, const CVector &v1) {
	mType = ELINE;
	mpParent = parent;//�e�ݒ�
	//�����̒��_�ݒ�
	mV[0] = v0;
	mV[1] = v1;
	//�X�P�[��1�{
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();//�s��X�V
	//�R���W�������X�g�ɒǉ�
	CollisionManager.Add(this);
	ChangePriority();
}

//CollisionTriangleLine(�O�p�R���C�_, �����R���C�_, �����l)
//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
bool CCollider::CollisionTriangleLine(CCollider *t, CCollider *l, CVector *a) {
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	v[0] = t->mV[0] * t->mMatrix * t->mpParent->mMatrix;
	v[1] = t->mV[1] * t->mMatrix * t->mpParent->mMatrix;
	v[2] = t->mV[2] * t->mMatrix * t->mpParent->mMatrix;
	sv = l->mV[0] * l->mMatrix * l->mpParent->mMatrix;
	ev = l->mV[1] * l->mMatrix * l->mpParent->mMatrix;
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
	//���_3���_1�x�N�g���ƒ��_3��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����l�v�Z�i�Փ˂��Ȃ��ʒu�܂Ŗ߂��j
	if (dots < 0.0f) {
		//�n�_���ʂ̌�������
		*a = normal * -dots;
	}
	else {
		//�I�_���ʂ̌�������
		*a = normal * -dote;
	}
	return true;
}

//CollisionTriangleLine(�O�p�R���C�_, �����R���C�_, �����l)
//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
bool CCollider::CollisionTriangleSphere(CCollider *t, CCollider *s, CVector *a) {
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	v[0] = t->mV[0] * t->mMatrix * t->mpParent->mMatrix;
	v[1] = t->mV[1] * t->mMatrix * t->mpParent->mMatrix;
	v[2] = t->mV[2] * t->mMatrix * t->mpParent->mMatrix;
	//�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();

	sv = s->mV[0] * s->mMatrix * s->mpParent->mMatrix + normal * s->mRadius;
	ev = sv - normal * s->mRadius * 2;
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
	//���_3���_1�x�N�g���ƒ��_3��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����l�v�Z�i�Փ˂��Ȃ��ʒu�܂Ŗ߂��j
	if (dots < 0.0f) {
		//�n�_���ʂ̌�������
		*a = normal * -dots;
	}
	else {
		//�I�_���ʂ̌�������
		*a = normal * -dote;
	}
	return true;
}

void CCollider::ChangePriority(){
	CMatrix matrix = mMatrix;//�R���C�_�̍s��ޔ�
	CVector position;//���_����̋����v�Z�p

	//mpCombinedMatrix
	//if (mpCombinedMatrix){
	//	//�X�L�����b�V���̏ꍇ�͍����s����K�p
	//	matrix = matrix * *mpCombinedMatrix;
	//}
	//else{
	if (mpParent){
		//�e������ΐe�̍����s����K�p
		matrix = matrix * mpParent->mMatrix;
	}
	/*}*/

	switch (mType){
	case ESPHERE://���R���C�_�̎��A���̒��S���W�����߂�
		position = CVector() * matrix;
		break;
	case ETRIANGLE://�O�p�`�̏d�S���W�����߂�
		//�O�p�`�̒��_���ړ������č��v
		position = mV[0] * matrix + mV[1] * matrix + mV[2] * matrix;
		position = position * (1.0 / 3.0f);//���v�l��3����1���d�S
		break;
	case ELINE://�����̒��S���W�����߂�
		//�n�_�ƏI�_���ړ������č��v
		position = mV[0] * matrix + mV[1] * matrix;
		position = position*(1.0 / 2.0f);//���v�l��2����1�����S
		break;
	}
	SetPriority(position.Length());
	CollisionManager.Remove(this);//���X�g����폜����
	CollisionManager.Add(this);//���X�g�ɒǉ�����
}

//ChangePriority(�D��x)
void CCollider::ChangePriority(int priority){
	SetPriority(priority);
	CollisionManager.Remove(this); //���X�g����폜����
	CollisionManager.Add(this); //���X�g�ɒǉ�����
}

/*�ǉ�*/
//�Փ˔���
//Collision(�R���C�_1, �R���C�_2, �����l)
//return:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
bool CCollider::Collision(CCollider *m, CCollider *y ,CVector *a) {
	//�e�R���C�_�̒��S���W�����߂�
	//���_�~�R���C�_�̕ϊ��s��~�e�̕ϊ��s��
	CVector mpos = CVector() * m->mMatrix * m->mpParent->mMatrix;
	CVector ypos = CVector() * y->mMatrix * y->mpParent->mMatrix;
	//���S���璆�S�ւ̃x�N�g�������߂�
	mpos = mpos - ypos;
	//���S�̋��������a�̍��v��菬�����ƏՓ�
	if (m->mRadius + y->mRadius > mpos.Length()) {
		if (mpos.Length() == 0){
			//���S�ɓ������W�̎��͔��a�̘a�̕��A��Ɉړ�������
			*a = CVector(0.0f, 1.0f, 0.0f) * (m->mRadius + y->mRadius);//CVector(0.0f, 0.1f, 0.0f);
		}
		else{
			*a = mpos.Normalize() * (m->mRadius + y->mRadius - mpos.Length());
		}
		//mpos.Length() 
		//�Փ˂��Ă���
		return  true;		
	}
	//�Փ˂��Ă��Ȃ�
	return false;
}