#pragma once

class CMatrix44;

class CVector2 {
public:
	float x, y;
	CVector2() : x(0), y(0) {}
	CVector2(float a, float b)
		: x(a), y(b) {}
};

class CVector3 {
public:
	float x, y, z;
	CVector3();
	CVector3(float x, float y, float z);
	//CMatrix44�Ƃ̊|���Z
	const CVector3 operator * (const CMatrix44 &m) const;
	/* CVector3���m�̉��Z
	*/
	const CVector3 operator + (const CVector3 &v) const;
	void operator += (const CVector3 &v);
	const CVector3 operator - (const CVector3 &v) const;
	void operator -= (const CVector3 &v);
	const CVector3 operator * (const CVector3 &v) const;
	void operator *= (const CVector3 &v);
	const CVector3 operator / (const CVector3 &v) const;
	void operator /= (const CVector3 &v);
	const CVector3 operator * (float f) const;
	void operator *= (float f);
	const CVector3 operator / (float f) const;
	void operator /= (float f);
	/*���ς����߂�
	�������Ax,y,z�̂�
	*/
	//29
	float dot(const CVector3 &v) const;
	/* �x�N�g���̑傫����Ԃ�
	�������Ax,y,z�̂�
	*/
	//30
	float length() const ;
	//float length();
	/* ���K�������x�N�g����Ԃ�
	�x�N�g���̐��K���F�傫����1�ɂ���
	*/
	//30
	CVector3 normalize() const ;
	/* �w�肳�ꂽ�x�N�g���̕����֌�����ׂ̉�]�p�x�𓾂�
	return:�bX���̉�]�p�x�@Y���̉�]�p�x�@�O�x�b
	*/
	CVector3 getRotationTowards(const CVector3 &dir);
	/* �w�肳�ꂽ���a�̋���̈ʒu�������_���ɐݒ肷��
	�x�N�g���b0.0 0.0 1.0�b��X���Ń����_���ɉ�]�����A����
	Y���Ń����_���ɉ�]�����A���a���|�����l��ݒ肷��
	*/
	void setRandomPositionSphere(float radius);
	//28
	/*
	�O�ς����߂�
	*/
	CVector3 Cross(const CVector3 &v) const {
		return CVector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x).normalize();
	}

};
