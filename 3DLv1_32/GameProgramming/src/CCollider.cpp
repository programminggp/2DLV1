//�R���C�_�N���X�̃C���N���[�h
#include"CCollider.h"
//�R���W�����}�l�[�W���N���X�̃C���N���[�h
#include"CCollisionManager.h"
//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"

//�f�t�H���g�R���X�g���N�^�̒�`
CCollider::CCollider()
	:mpParent(nullptr)
	, mpMatrix(&mMatrix)
	, mType(ESPHERE)
	, mRadius(0)
{
	//�R���W�����}�l�[�W���ɒǉ�
	CCollisionManager::Get()->Add(this);
}

CCollider::CCollider(CCharacter* parent, CMatrix* matrix,
	const CVector& position, float radius) 
:CCollider()
{
	//�e�ݒ�
	mpParent = parent;
	//�e�s��ݒ�
	mpMatrix = matrix;
	//CTransform�ݒ�
	mPosition = position; //�ʒu
	//���a�ݒ�
	mRadius = radius;
	//�R���W�����}�l�[�W��y�ɒǉ�
	//CCollisionManager::Get()->Add(this);
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
	//�O�p�`�̒��_��������I�_�ւ̃x�N�g�������߂�
	CVector v0ev = ev - v[0];
	//�������ʂƌ������Ă��邩���ςŊm�F����
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	if (dots * dote >= 0.0f) {
		//�Փ˂��Ă��Ȃ�(�����s�v)
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//�ʂƐ����̌�_�����߂�
	//��_�̌v�Z
	CVector cross = sv + (ev - sv) * (abs(dots)/(abs(dots) + abs(dote)));

	//��_���O�p�`���Ȃ�Փ˂��Ă���
	//���_1���_2�x�N�g���ƒ��_1��_�x�N�g���s�̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	
	//���_2���_3�x�N�g���ƒ��_2��_�x�N�g���O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		//�Փ˂��Ă��Ȃ�(�����s�v)
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//�ۑ�32
	//���_3���_1�x�N�g���ƒ��_3��_�x�N�g���O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
			//�Փ˂��Ă��Ȃ�(�����s�v)
			*a = CVector(0.0f, 0.0f, 0.0f);
			return false;
	}

	//�����͖ʂƌ������Ă���
	//�����l�v�Z(�Փ˂��Ȃ��ʒu�܂Ŗ߂�)
	if (dots < 0.0f)
	{
		//�n�_������
		*a = normal * -dots;
	}
	else {
		//�I�_������
		*a = normal * -dote;
	}
	return true;
}

CCharacter* CCollider::Parent() 
{
	return mpParent;
}

void CCollider::Render() 
{
	glPushMatrix();
	//�R���C�_�̒��S���W���v�Z
	//�����̍��W�~�e�̕ϊ��s����|����
	CVector pos = mPosition * *mpMatrix;
	//���S���W�ֈړ�
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//���`��
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}
//�Փ˔���
//Collision(�R���C�_1,�R���C�_2)
//retrun:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
bool CCollider::Collision(CCollider* m, CCollider* o) {
	//�e�R���C�_�̒��S���W�����߂�
	//���_�~�R���C�_�̕ϊ��s��~�e�̕ϊ��s��
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	//���S���璆�S�ւ̃x�N�g�������߂�
	mpos = mpos - opos;
	//���S�̋��������a�̍��v��菬�����ƏՓ�
	if (m->mRadius + o->mRadius > mpos.Length()){
		//�Փ˂��Ă���
		return true;
	}
	//�Փ˂��Ă��Ȃ�
	return false;
}
CCollider::~CCollider() {
	//�R���W�������X�g����폜
	CCollisionManager::Get()->Remove(this);

}
int CCollider::Type() {
	return mType;
}