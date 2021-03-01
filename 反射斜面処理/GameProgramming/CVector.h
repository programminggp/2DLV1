#ifndef CVECTOR_H
#define CVECTOR_H
//CMatrix�N���X�̃C���N���[�h
#include "CMatrix.h"
/*
 �x�N�g���N���X
 �x�N�g���f�[�^�������܂�
*/
class CVector {
public:
	//3D�e���ł̒l��ݒ�
	float mX, mY, mZ;
	//�e���ł̒l�̐ݒ�
	//Set(X���W, Y���W, Z���W)
	void Set(float x, float y, float z);
	//�s��Ƃ̊|���Z
	//Multi(�s��)
	CVector Multi(const CMatrix &m);
	//�f�t�H���g�R���X�g���N�^
	CVector();
	//�R���X�g���N�^
	//CVector(X���W, Y���W, Z���W)
	CVector(float x, float y, float z);
	//*���Z�q�̃I�[�o�[���[�h
	//CVector * CMatrix �̉��Z���ʂ�Ԃ�
	CVector operator*(const CMatrix &m);
	//-���Z�q�̃I�[�o�[���[�h
	//CVector - CVector �̉��Z���ʂ�Ԃ�
	CVector operator-(const CVector &v);
	//�x�N�g���̒�����Ԃ�
	float Length() const ;
	//����
	//Dot(�x�N�g��)
	float Dot(const CVector &v);
	//���K��
	//�傫��1�̃x�N�g����Ԃ�
	CVector Normalize() const ;
	//�O��
	//Cross(�x�N�g��)
	CVector Cross(const CVector &v) const;
	//*���Z�q�̃I�[�o�[���[�h
	//CVector * float �̉��Z���ʂ�Ԃ�
	CVector operator*(const float &f) const ;
	//+���Z���̃I�[�o�[���[�h
	//CVector + CVector �̉��Z���ʂ�Ԃ�
	CVector operator+(const CVector &v);

	//�x�N�g������I�C���[�p�����߂�
	//foward:�O�����x�N�g��
	//up:������x�N�g��
	static CVector Euler(const CVector &foward, const CVector &up);
	//���x�N�g������I�C���[�p�����߂�
	//up:������x�N�g��
	CVector Euler(const CVector &up);

};

#endif
