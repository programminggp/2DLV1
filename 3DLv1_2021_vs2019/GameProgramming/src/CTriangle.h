#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CVector.h"
#include "CMatrix.h"

/*
�O�p�`�N���X
*/
class CTriangle {
public:
	CTriangle();
	//�}�e���A���ԍ��̎擾
	int MaterialIdx();
	//�}�e���A���ԍ��̐ݒ�
	//Material(�}�e���A���ԍ�)
	void MaterialIdx(int idx);
	//���_���W�𓾂�
	const CVector& V0() const;
	const CVector& V1() const;
	const CVector& V2() const;
	//�@���𓾂�
	const CVector& N0() const;
	const CVector& N1() const;
	const CVector& N2() const;
	//UV�𓾂�
	const CVector& UV0() const;
	const CVector& UV1() const;
	const CVector& UV2() const;
	//UV�ݒ�
	//SetUV(const CVector &v0, const CVector &v1, const CVector &v2)
	void SetUv(const CVector& v0, const CVector& v1, const CVector& v2);
	//���_���W�ݒ�
	//Vertex(���_1, ���_2, ���_3)
	void Vertex(const CVector &v0, const CVector &v1, const CVector &v2);
	//�@���ݒ�
	//Normal(�@���x�N�g��)
	void Normal(const CVector &n);
	//Normal(�@���x�N�g��1, �@���x�N�g��2, �@���x�N�g��3)
	void Normal(const CVector &v0, const CVector &v1, const CVector &v2);
	//�`��
	void Render();
	//�`��
	void Render(const CMatrix &m);
private:
	CVector mV[3]; //���_���W
	CVector mN[3]; //�@��
	CVector mUv[3]; //�e�N�X�`���}�b�s���O
	int mMaterialIdx; //�}�e���A���ԍ�
};

#endif
