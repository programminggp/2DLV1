#include "CVector4.h"
#include "CMatrix44.h"
#define _USE_MATH_DEFINES	//���w���C�u������M_PI��L���ɂ���
#include <math.h>	//���w���C�u�����̃C���N���[�h
#include "stdlib.h"

CVector4::CVector4() : w(1.0f) {}

CVector4::CVector4(float x, float y, float z) : CVector3(x, y, z), w(1.0f) {}

CVector4::CVector4(float x, float y, float z, float w) : CVector3(x, y, z), w(w) {}

//CMatrix44�Ƃ̊|���Z
const CVector4 CVector4::operator * (const CMatrix44 &m) const {
	CVector4 tmp;
	tmp.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + w * m.m[3][0];
	tmp.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + w * m.m[3][1];
	tmp.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + w * m.m[3][2];
	tmp.w = x * m.m[0][3] + y * m.m[1][3] + z * m.m[2][3] + w * m.m[3][3];
	return tmp;
}

/* CVector4���m�̉��Z
�������Ax,y,z�̂�
*/
const CVector4 CVector4::operator + (const CVector4 &v) const {
	CVector4 tmp;
	tmp.x = x + v.x;
	tmp.y = y + v.y;
	tmp.z = z + v.z;
	return tmp;
}
/* CVector4��float�̊|���Z
�������Ax,y,z�̂�
*/
const CVector4 CVector4::operator * (float f) const {
	CVector4 tmp;
	tmp.x = x * f;
	tmp.y = y * f;
	tmp.z = z * f;
	return tmp;
}
/*���ς����߂�
�������Ax,y,z�̂�
*/
float CVector4::dot(const CVector4 &v) {
	return x*v.x + y*v.y + z*v.z;
}
/* �x�N�g���̑傫����Ԃ�
�������Ax,y,z�̂�
*/
float CVector4::length() {
	return sqrt(x*x + y*y + z*z);
}
/* ���K�������x�N�g����Ԃ�
�x�N�g���̐��K���F�傫����1�ɂ���
*/
CVector4 CVector4::normalize() {
	float len = length();
	return CVector4(x / len, y / len, z / len);
}
/* �w�肳�ꂽ�x�N�g���̕����֌�����ׂ̉�]�p�x�𓾂�
return:�bX���̉�]�p�x�@Y���̉�]�p�x�@�O�x�b
*/
CVector4 CVector4::getRotationTowards(const CVector4 &dir) {
	//�ړI�ƂȂ�x�N�g���́AXZ���ʏ�ł̒��������߂�
	float sx = sqrt(dir.x*dir.x + dir.y*dir.y);
	//�ړI�ƂȂ�x�N�g���ł�X���ł̉�]�p�x�AY���ł̉�]�p�x�����߂�
	CVector4 rot = CVector4(atan2f(-dir.y, sx)*180.0f / M_PI, atan2f(-dir.z, dir.x)*180.0f / M_PI, 0.0f);
	//�����̃x�N�g���́AXZ���ʏ�ł̒��������߂�
	sx = sqrt(x * x + z * z);
	//�����̃x�N�g���ł�X���ł̉�]�p�x�AY���ł̉�]�p�x�����߂�
	CVector4 rot1(atan2f(-y, sx)*180.0f / M_PI, atan2f(-z, x)*180.0f / M_PI, 0.0f);
	//�}�C�i�X�̊p�x�̓v���X�̊p�x�֕ϊ�����i0�x�`360�x�̊Ԃɂ���j
	if (rot.x < 0.0f) rot.x += 360.0f;
	if (rot.y < 0.0f) rot.y += 360.0f;
	if (rot1.x < 0.0f) rot1.x += 360.0f;
	if (rot1.y < 0.0f) rot1.y += 360.0f;
	//�ړI�̉�]�l�Ǝ����̉�]�l�Ƃ̍������߂�
	rot1 = rot + rot1 * -1.0f;
	//�}�C�i�X�̊p�x�̓v���X�̊p�x�֕ϊ�����i0�x�`360�x�̊Ԃɂ���j
	if (rot1.x < 0.0f) rot1.x += 360.0f;
	if (rot1.y < 0.0f) rot1.y += 360.0f;
	return rot1;	//���߂��p�x��߂�
}
/* �w�肳�ꂽ���a�̋���̈ʒu�������_���ɐݒ肷��
�x�N�g���b0.0 0.0 1.0�b��X���Ń����_���ɉ�]�����A����
Y���Ń����_���ɉ�]�����A���a���|�����l��ݒ肷��
*/
void CVector4::setRandomPositionSphere(float radius) {
	CMatrix44 rotx, roty;
	rotx.rotationX(rand() % 360);	//X���̉�]�s����쐬
	roty.rotationY(rand() % 360);	//Y���̉�]�s����쐬
	CVector4 vec(0.0f, 0.0f, 1.0f);	//�x�N�g���쐬
	vec = vec * rotx * roty * radius;	//��]�����a���|����
	//�x�N�g���l��ݒ肷��
	x = vec.x;
	y = vec.y;
	z = vec.z;
}
