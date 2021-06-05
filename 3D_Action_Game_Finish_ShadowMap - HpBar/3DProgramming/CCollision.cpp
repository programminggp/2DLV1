#include "CCollision.h"
/*
���R���C�_�Ƌ��R���C�_�̏Փ˔���
true:�Փ˂��Ă���@false:�Փ˂��Ă��Ȃ�
m:�����̃R���C�_�@y:����̃R���C�_
*/
bool CCollision::Sphere(CCollider *m, CCollider *y) {
	//���S���璆�S�ւ̃x�N�g�������߂܂�
	CVector3 dir = m->mPosition - y->mPosition;
	//���S�����Ɣ��a�̍��v���r���A���S���������������
	//�Փ˂��Ă��܂�
	return dir.length() < m->mRadius + y->mRadius;
}
/*
�J�v�Z���ƎO�p�`�R���C�_�̏Փ˔���
true:�Փ˂��Ă��� false:�Փ˂��Ă��Ȃ�
capsule:�J�v�Z���R���C�_ triangle:�O�p�`�R���C�_
adjust:�Փ˂��Ȃ��ʒu�܂ł̈ړ���
*/
bool CCollision::CapsuleTriangle(CCollider *capsule, CCollider *triangle, CVector3 *adjust) {
	//�J�v�Z���L���X�g�ɃL���X�g
	CCapsuleCollider *c = (CCapsuleCollider*)capsule;
	//�O�p�`�R���C�_�ɃL���X�g
	CTriangleCollider *t = (CTriangleCollider*)triangle;
	//�����ƎO�p�`�̏Փ˔�����Ă�
	if (LineTriangle(c->mV[0], c->mV[1], t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	//���̋��ƎO�p�`�̏Փ˔���
	CVector3 center = (c->mV[1] - c->mV[0]).normalize() * c->mRadius + c->mV[0];
	if (SphereTriangle(center, c->mRadius, t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	//��̋��ƎO�p�`�̏Փ˔���
	center = (c->mV[0] - c->mV[1]).normalize() * c->mRadius + c->mV[1];
	if (SphereTriangle(center, c->mRadius, t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	//�����ƎO�p�`�̏Փ˔�����Ă�
	if (LineTriangle(c->mV[2], c->mV[3], t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	//�����ƎO�p�`�̏Փ˔�����Ă�
	if (LineTriangle(c->mV[4], c->mV[5], t->mV[0], t->mV[1], t->mV[2], adjust)) {
		return true;
	}
	return false;
}
/*
���ƎO�p�`�̏Փ˔���
true:�Փ˂��Ă��� false:�Փ˂��Ă��Ȃ�
p0,p1:�� p0�� p1��
v0,v1,v2:�O�p�`
adjust:�Փ˂��Ȃ��ʒu�܂ł̈ړ���
*/
bool CCollision::LineTriangle(const CVector3 &p0, const CVector3 &p1, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, CVector3 *adjust) {
	//���Ɩʂ̌����𔻒�
	CVector3 v01 = v1 - v0;
	CVector3 v02 = v2 - v0;
	CVector3 normal = v01.Cross(v02); //�@���i�ʂ̌����j
	CVector3 vp00 = p0 - v0;
	CVector3 vp01 = p1 - v0;
	float dot0 = vp00.dot(normal);
	float dot1 = vp01.dot(normal);
	if (dot0 * dot1 >= 0) {
		//�������Ă��Ȃ�
		return false;
	}
	//��������_���Z�o
	//�ǂ������Βl�ɂ���
	if (dot0 < 0) {
		dot0 *= -1;
	}
	else {
		dot1 *= -1;
	}
	dot1 += dot0;	//���������߂�
	dot0 = dot0 / dot1;	//p0���ʂ܂ł̊���
	//��_�Z�o
	CVector3 cross = p0 + (p1 - p0) * dot0;
	//��_���O�p�`��������
	if (PointInTriangle(cross, v0, v1, v2, normal)) {
		//�O�p�`���ł���
		*adjust = normal * (((p1 - p0) * dot0).dot(normal));
		return true;
	}
	//�O�p�`�̊O
	return false;
}
/*
�_���O�p�`�������肷��
true;�O�p�`�� false:�O�p�`�O
p0:�_���W
v0v1v2:�O�p�`�̒��_���W
n:�O�p�`�̖@���x�N�g��
*/
bool CCollision::PointInTriangle(const CVector3 &p0, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &n) {
	CVector3 pvn;
	//v1��v0�̍��֓_������Ζ@�������
	pvn = (v1 - v0).Cross(p0 - v0);
	if (pvn.dot(n) < 0) return false;
	//v2��v1�̍��֓_������Ζ@�������
	pvn = (v2 - v1).Cross(p0 - v1);
	if (pvn.dot(n) < 0) return false;
	//v0��v2�̍��֓_������Ζ@�������
	pvn = (v0 - v2).Cross(p0 - v2);
	if (pvn.dot(n) < 0) return false;
	return true;
}
//30
/*
���ƎO�p�`�̏Փ˔���
true:�Փ˂��Ă��� false:�Փ˂��Ă��Ȃ�
c:���̒��S���W r:���̔��a
v0,v1,v2:�O�p�`
adjust:�Փ˂��Ȃ��ʒu�܂ł̈ړ���
*/
bool CCollision::SphereTriangle(const CVector3 &c, float r, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, CVector3 *adjust) {
	//�ʂ̖@���v�Z
	CVector3 v01 = v1 - v0;
	CVector3 v02 = v2 - v0;
	CVector3 normal = v01.Cross(v02); //�@���i�ʂ̌����j
	//���ƖʂƂ̐ړ_���O�p�`�������肷��
	//���̒��S����ړ_�ւ����Ă̐����̒[�����߂�
	CVector3 p0 = c + normal * -r;
	CVector3 p1 = c + normal * r;
	//���ƎO�p�`�̏Փˏ���
	return LineTriangle(p0, p1, v0, v1, v2, adjust);
}
