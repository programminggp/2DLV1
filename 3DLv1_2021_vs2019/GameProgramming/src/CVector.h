#ifndef CVECTOR_H
#define CVECTOR_H
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
	//�f�t�H���g�R���X�g���N�^
	CVector();
	//�R���X�g���N�^
	//CVector(X���W, Y���W, Z���W)
	CVector(float x, float y, float z);
	//CVector * CMatrix�̌��ʂ�CVector�ŕԂ�
	CVector operator*(const CMatrix &m);
	//-���Z�q�̃I�[�o�[���[�h
	//CVector - CVector �̉��Z���ʂ�Ԃ�
	CVector operator-(const CVector &v);
	//�x�N�g���̒�����Ԃ�
	float Length();
	//����
	//Dot(�x�N�g��)
	float Dot(const CVector &v);
	//�O��
	//Cross(�x�N�g��)
	CVector Cross(const CVector &v);
	//*���Z�q�̃I�[�o�[���[�h
	//CVector * float �̉��Z���ʂ�Ԃ�
	CVector operator*(const float &f);
	//���K��
	//�傫��1�̃x�N�g����Ԃ�
	CVector Normalize();
	//+���Z�q�̃I�[�o�[���[�h
	//CVector + CVector �̉��Z���ʂ�Ԃ�
	CVector operator+(const CVector &v);
	//Y���ł̉�]�p�x�̎擾
	//�x�x��Ԃ��iZ���{��0�x�j
	float GetRotationY();
	//X���ł̉�]�p�x�̎擾
	//�x�x��Ԃ��iZ���{��0�x�j
	//GetRotationX(Y������)
	float GetRotationX(CVector& y);

};
#endif
