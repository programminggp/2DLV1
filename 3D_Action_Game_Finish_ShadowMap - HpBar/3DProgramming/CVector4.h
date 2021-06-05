#pragma once

#include "CVector3.h"

class CMatrix44;

/* 4�����i3�����j�x�N�g���N���X�̒�`
3�������W�i3�����x�N�g���j�ƁA
4�~4�s��Ƃ̉��Z���s��
1�s4��̍s��
*/
class CVector4 : public CVector3 {
public:
	float w;	//w�F1.0

	CVector4();

	CVector4(float x, float y, float z);
	CVector4(float x, float y, float z, float w);

	//CMatrix44�Ƃ̊|���Z
	const CVector4 operator * (const CMatrix44 &m) const;

	/* CVector4���m�̉��Z
	�������Ax,y,z�̂�
	*/
	const CVector4 operator + (const CVector4 &v) const;
	/* CVector4��float�̊|���Z
	�������Ax,y,z�̂�
	*/
	const CVector4 operator * (float f) const;
	/*���ς����߂�
	�������Ax,y,z�̂�
	*/
	float dot(const CVector4 &v);
	/* �x�N�g���̑傫����Ԃ�
	�������Ax,y,z�̂�
	*/
	float length();
	/* ���K�������x�N�g����Ԃ�
	�x�N�g���̐��K���F�傫����1�ɂ���
	*/
	CVector4 normalize();
	/* �w�肳�ꂽ�x�N�g���̕����֌�����ׂ̉�]�p�x�𓾂�
	return:�bX���̉�]�p�x�@Y���̉�]�p�x�@�O�x�b
	*/
	CVector4 getRotationTowards(const CVector4 &dir);
	/* �w�肳�ꂽ���a�̋���̈ʒu�������_���ɐݒ肷��
	�x�N�g���b0.0 0.0 1.0�b��X���Ń����_���ɉ�]�����A����
	Y���Ń����_���ɉ�]�����A���a���|�����l��ݒ肷��
	*/
	void setRandomPositionSphere(float radius);
};
