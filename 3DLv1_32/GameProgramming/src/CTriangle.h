#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include"CVector.h"

/*
�O�p�`�N���X
*/
class CTriangle {
public:
	//���_���W�ݒ�
	//Vertex(���_1�C���_2,���_3,)
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2);
	//�@���ݒ�
	//Normal(�@���x�N�g��)
	void Normal(const CVector& n);
	//Normal(�@���x�N�g��1,�@���x�N�g��2,�@���x�N�g��3)
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2);
	//�`��
	void Render();
	//�}�e���A���ԍ��̎擾
	int MaterialIdx();
	//�}�e���A���ԍ��̐ݒ�
	//Matrial(�}�e���A���ԍ�)
	void MaterialIdx(int idx);
	//UV�ݒ�
	void SetUv(const CVector& v0, const CVector& v1, const CVector& v2);
	//�`��
	//Render(�s��)
	void Render(const CMatrix& m);

	//���_���W�𓾂�
	const CVector& V0() const; //mV[0]��Ԃ��܂�
	const CVector& V1() const; //mV[1]��Ԃ��܂�
	const CVector& V2() const; //mV[2]��Ԃ��܂�

	//���_���W�𓾂�
	const CVector& N0() const; //mN[0]��Ԃ��܂�
	const CVector& N1() const; //mN[1]��Ԃ��܂�
	const CVector& N2() const; //mN[2]��Ԃ��܂�

	//���_���W�𓾂�
	const CVector& UV0() const; //mUV[0]��Ԃ��܂�
	const CVector& UV1() const; //mUV[1]��Ԃ��܂�
	const CVector& UV2() const; //mUV[2]��Ԃ��܂�
private:
	CVector mV[3]; //���_���W
	CVector mN[3]; //�@��
	CVector mUv[3]; //�e�N�X�`���}�b�s���O
	int mMaterialIdx; //�}�e���A���ԍ�
};
#endif 
