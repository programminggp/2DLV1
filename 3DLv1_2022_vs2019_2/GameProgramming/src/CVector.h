#ifndef CVECTOR_H
#define CVECTOR_H
#include "CMatrix.h"

/*
 �x�N�g���N���X
 �x�N�g���f�[�^�������܂�
*/
class CVector {
public:
	//���K��
	//�傫��1�̃x�N�g����Ԃ�
	CVector Normalize() const;
	//�O��
	//Cross(�x�N�g��)
	CVector Cross(const CVector& v) const;
	//*���Z�q�̃I�[�o�[���[�h
	//CVector * float �̉��Z���ʂ�Ԃ�
	CVector operator*(const float& f) const;

	//����
	//Dot(�x�N�g��)
	float Dot(const CVector& v) const;

	//�x�N�g���̒�����Ԃ�
	float Length() const;
	//�e���ł̒l�̐ݒ�
	//Set(X���W, Y���W, Z���W)
	void Set(float x, float y, float z);
	//X�̒l�𓾂�
	float X() const;
	//Y�̒l�𓾂�
	float Y() const;
	//Z�̒l�𓾂�
	float Z() const;
	//�f�t�H���g�R���X�g���N�^
	CVector();
	//�R���X�g���N�^
	//CVector(X���W, Y���W, Z���W)
	CVector(float x, float y, float z);
	//+���Z�q�̃I�[�o�[���[�h
	//CVector + CVector �̉��Z���ʂ�Ԃ�
	CVector operator+(const CVector& v) const;
	//-���Z�q�̃I�[�o�[���[�h
	//CVector - CVector �̉��Z���ʂ�Ԃ�
	CVector operator-(const CVector& v) const;
	//CVector * CMatrix�̌��ʂ�CVector�ŕԂ�
	CVector operator*(const CMatrix& m);

private:
	//3D�e���ł̒l��ݒ�
	float mX, mY, mZ;
};
#endif
